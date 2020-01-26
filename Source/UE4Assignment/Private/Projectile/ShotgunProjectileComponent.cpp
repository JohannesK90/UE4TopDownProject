// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/ShotgunProjectileComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Weapon/WeaponBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UShotgunProjectileComponent::UShotgunProjectileComponent()
{
}


// Called when the game starts
void UShotgunProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShotgunProjectileComponent::Fire(float Velocity, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine)
{
	if (!ProjectileClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProjectileClass is null. (ShotgunProjectileComponent -> ProjectileClass -> BP_Projectile)"));
		return;
	}

	AWeaponBase* Weapon = Cast<AWeaponBase>(GetOwner());

	// Shotgun Ammo Reduce Logic
	if (Weapon->CurrentAmmo <= 0)
	{
		return;
	}
	if (Weapon->CurrentAmmo <= NumOfBullets)
	{
		NumOfBullets = Weapon->CurrentAmmo;
	}
	Weapon->CurrentAmmo -= NumOfBullets;

	// Spawn NumOfBullets at owner(weapon)'s muzzle
	FTransform MuzzleTransform = Weapon->WeaponMesh->GetSocketTransform("muzzle");
	FVector MuzzleLocation = MuzzleTransform.GetLocation();
	FRotator MuzzleRotation = MuzzleTransform.GetRotation().Rotator();

	for (int i = 0; i < NumOfBullets; i++)
	{
		// set random muzzle's rotation 
		FRotator RandomRotation = MuzzleRotation.Add(0.0f, FMath::RandRange(-MaxFireAngle / 2, MaxFireAngle / 2), 0.0f);
		MuzzleTransform.SetRotation(RandomRotation.Quaternion());

		// SpawnActorDeferred -> modify projectile's initialLifeSpan with BulletRange -> FinishSpawningActor
		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, MuzzleTransform);
		Projectile->SetupMovement(Velocity, BulletRange);
		UGameplayStatics::FinishSpawningActor(Projectile, MuzzleTransform);

		FVector LaunchDirection = RandomRotation.Vector();
		Projectile->FireInDirection(LaunchDirection);

		// set the muzzle's rotation back to default
		MuzzleTransform.SetRotation(MuzzleRotation.Quaternion());

		// Debug only
		if (bDrawDebugLine)
		{
			FVector Start = MuzzleLocation + MuzzleRotation.Vector();
			FVector End = MuzzleLocation + RandomRotation.Vector() * BulletRange;
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.5f, 0, 0.0f);
		}
	}

}