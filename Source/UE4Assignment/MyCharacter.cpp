// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

#include "UE4Assignment\Public\Interact\InteractInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Weapon/WeaponBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Set the inventory size, whit all empty elements
	WeaponInventory.Init(nullptr, InventorySize);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	bDead = false;
}
// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyCharacter::Interact);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::EndFire);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::Reload);

}

void AMyCharacter::MouseTrace(FVector CameraPosition, FVector MouseDirection)
{

	FPlane PlayerViewPlane = FPlane(GetActorLocation(), FVector(0.0f, 0.0f, 1.0f));
	FVector CleanDirection = FVector(MouseDirection.X, MouseDirection.Y, 0.0f);

	FVector Intersection;
	float T;
	UKismetMathLibrary::LinePlaneIntersection(CameraPosition, MouseDirection * 10000.0f, PlayerViewPlane, T, Intersection);


	UKismetSystemLibrary::DrawDebugPoint
	(
		this,
		Intersection,
		3.0F,
		FLinearColor::Green,
		10.0f
	);

	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Intersection);
	GetController()->SetControlRotation(PlayerRot);

	FString tempLog = CleanDirection.ToString();

	// Interact RayTrace
	FVector RayTraceStartPosition = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + RayTraceZOffset);
	FVector LineStart = RayTraceStartPosition + this->GetViewRotation().Vector();
	FVector LineEnd = RayTraceStartPosition + this->GetViewRotation().Vector() * InteractRayTraceLength;

	DrawDebugLine(
		GetWorld(),
		LineStart,
		LineEnd,
		FColor::Orange,
		false,
		0.5f,
		0,
		0.0f
	);


	FHitResult HitResult;
	FCollisionQueryParams LineParams(FName(""), false, GetOwner());

	GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		LineStart,
		LineEnd,
		ECC_Visibility,
		LineParams
	);

	AActor* InteractableActor = HitResult.GetActor();
	if (InteractableActor)
	{
		if (InteractableActor != FocusedActor)
		{
			if (FocusedActor)
			{
				IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
				if (Interface)
				{
					Interface->Execute_EndFocus(FocusedActor);
				}
			}
			IInteractInterface* Interface = Cast<IInteractInterface>(InteractableActor);
			if (Interface)
			{
				Interface->Execute_StartFocus(InteractableActor);
			}
			FocusedActor = InteractableActor;
		}
	}
	else
	{
		if (FocusedActor)
		{
			IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
			if (Interface)
			{
				Interface->Execute_EndFocus(FocusedActor);
			}
		}
		FocusedActor = nullptr;
	}
}

void AMyCharacter::MoveForward(float Axis)
{

	if (!bDead)
	{
		/*const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);*/
		const FVector Direction(1, 0, 0);
		AddMovementInput(Direction, Axis);
	}

}

void AMyCharacter::MoveRight(float Axis)
{

	/*const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);*/

	const FVector Direction(0, 1, 0);

	AddMovementInput(Direction, Axis);

}

void AMyCharacter::Interact()
{
	if (FocusedActor)
	{
		IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface)
		{
			Interface->Execute_OnInteract(FocusedActor, GetOwner());

			if (AWeaponBase* HitWeapon = Cast<AWeaponBase>(FocusedActor))
			{
				EquipWeapon(HitWeapon);
			}
		}
	}
}

void AMyCharacter::EquipWeapon(AWeaponBase* Weapon)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->DetachRootComponentFromParent();
		CurrentWeapon->SetSimulatePhysics(true);
		CurrentWeapon->SetActorEnableCollision(true);
	}

	CurrentWeapon = Weapon;
	CurrentWeapon->DisableComponentsSimulatePhysics();
	CurrentWeapon->SetActorEnableCollision(false);
	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("hand_r_weapon"));

	for (int i = 0; i < InventorySize; i++)
	{
		if (WeaponInventory[i] == nullptr)
		{
			WeaponInventory[i] = Weapon;
			break;
		}
		//TODO: What if all the slots are occupied, then we should remove the current equiped whit the new weapon.
	}
}

void AMyCharacter::StartFire()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->StartFire();
	}
}

void AMyCharacter::EndFire()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->EndFire();
	}
}

void AMyCharacter::Reload()
{
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->Reload();
	}
}