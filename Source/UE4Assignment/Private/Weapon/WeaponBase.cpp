// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <UE4Assignment\MyPlayerController.h>
#include <Runtime\Engine\Public\DrawDebugHelpers.h>

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
	if (!bIsReloading)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::StartFire()"));
	}
}

void AWeaponBase::EndFire_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::EndFire() "));
}

void AWeaponBase::Reload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::Reload() "));
}

void AWeaponBase::FireBullet(float Velocity, float RateOfFire, float RecoilForce, float BulletRange)
{
	if (!bIsReloading)
	{
		AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		FVector Start = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Vector();
		FVector End = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Add(0.0f, FMath::RandRange(-RecoilForce, RecoilForce), 0.0f).Vector() * BulletRange;

		FRotator MouseDir = UKismetMathLibrary::FindLookAtRotation(Start, End);
		WeaponMuzzle->SetWorldRotation(MouseDir);

		ABulletProjectile* Bullet = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ProjectileClass, WeaponMuzzle->GetComponentTransform());
		
		Bullet->SetupBullet(Velocity, BulletRange);
		UGameplayStatics::FinishSpawningActor(Bullet, WeaponMuzzle->GetComponentTransform());


		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			FColor::Blue,
			false,
			0.5f,
			0,
			0.0f
		);
	}
}

