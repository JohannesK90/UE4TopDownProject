// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Misc/Attribute.h"
#include <UE4Assignment\MyPlayerController.h>
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Projectile/Projectile.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetCollisionProfileName(TEXT("BlockAll"));
	WeaponMesh->SetSimulatePhysics(true);
	RootComponent = WeaponMesh;

	if (WeaponMuzzle == nullptr)
	{
		WeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
		WeaponMuzzle->SetupAttachment(WeaponMesh);
	}
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = AmmoClip;
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AWeaponBase::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("On Interact"));

	//Destroy();
}
 
void AWeaponBase::StartFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Focus : %s"), *this->GetName());
}

void AWeaponBase::EndFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Focus"));
}

void AWeaponBase::SetSimulatePhysics(bool value)
{
	WeaponMesh->SetSimulatePhysics(value);
}

void AWeaponBase::StartFire_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Fire Called");
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &AWeaponBase::FireLineTrace, 1.0f, 1.0f, 1000.0f);
	GetWorldTimerManager().SetTimer(AutomaticFireHandle, Delegate, 0.1f, true, 0.1f);
}

void AWeaponBase::EndFire_Implementation()
{

	GetWorldTimerManager().ClearAllTimersForObject(this);
}

void AWeaponBase::Reload()
{
	if (AmmoPool <= 0 || CurrentAmmo >= AmmoClip)
	{
		return;
	}

	if (AmmoPool < (AmmoClip - CurrentAmmo))
	{
		CurrentAmmo += AmmoPool;
		AmmoPool = 0;
	}
	else
	{
		AmmoPool -= AmmoClip - CurrentAmmo;
		CurrentAmmo = AmmoClip;
	}
}

void AWeaponBase::FireBullet(float Velocity, float RateOfFire, float RecoilForce, float BulletRange)
{
	//if (CurrentAmmo <= 0) 
	//{
	//	return; 
	//}
	//CurrentAmmo -= 1;

	//if (!bIsReloading)
	//{
	//	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//	FVector Start = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Vector();
	//	FVector End = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Add(0.0f, FMath::RandRange(-RecoilForce, RecoilForce), 0.0f).Vector() * BulletRange;

	//	FRotator MouseDir = UKismetMathLibrary::FindLookAtRotation(Start, End);
	//	WeaponMuzzle->SetWorldRotation(MouseDir);

	//	AProjectile* Bullet = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, WeaponMuzzle->GetComponentTransform());
	//	Bullet->SetupMovement(Velocity, BulletRange);
	//	UGameplayStatics::FinishSpawningActor(Bullet, WeaponMuzzle->GetComponentTransform());

	//	DrawDebugLine(GetWorld(),Start, End, FColor::Blue, false, 0.5f, 0, 0.0f);
	//}
}

void AWeaponBase::FireLineTrace(float RateOfFire, float RecoilForce, float BulletRange)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Trace Called");

	FHitResult OutHit;
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	FVector Start = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Vector();
	FVector End = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Add(0.0f, FMath::RandRange(-RecoilForce, RecoilForce), 0.0f).Vector() * BulletRange;

	FRotator MouseDir = UKismetMathLibrary::FindLookAtRotation(Start, End);
	WeaponMuzzle->SetWorldRotation(MouseDir);
	
	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, 10.0f);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Trace end");
	
}
