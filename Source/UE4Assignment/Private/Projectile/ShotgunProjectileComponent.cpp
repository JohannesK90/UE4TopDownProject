// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/ShotgunProjectileComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Weapon/WeaponBase.h"
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <Engine/Engine.h>

// Sets default values for this component's properties
UShotgunProjectileComponent::UShotgunProjectileComponent()
{}

// Called when the game starts
void UShotgunProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UShotgunProjectileComponent::StartFire(float BulletSpeed, float FireRate, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine)
{
	Delegate.BindUObject(this, &UShotgunProjectileComponent::Fire, BulletSpeed, FireRate, NumOfBullets, BulletRange, MaxFireAngle, bDrawDebugLine);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, Delegate, FireRate, true, 0.0f);
}

void UShotgunProjectileComponent::Fire(float BulletSpeed, float FireRate, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine)
{
	if (bFireDelayTimerExpired)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(GetOwner());

		if (!Weapon->ProjectileClass)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProjectileClass is null."));
			return;
		}

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
			AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(Weapon->ProjectileClass, MuzzleTransform);
			Projectile->SetupMovement(BulletSpeed, BulletSpeed, BulletRange);
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

		FireDelayTimer(FireRate);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		Delegate.BindUObject(this, &UShotgunProjectileComponent::Fire, BulletSpeed, FireRate, NumOfBullets, BulletRange, MaxFireAngle, bDrawDebugLine);
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, Delegate, FireRate, true, 0.0f);
	}
}

void UShotgunProjectileComponent::EndFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void UShotgunProjectileComponent::FireDelayTimer(float FireRate)
{
	// If the timer has expired or does not exist, start it  
	if ((FireDelayTimerHandle.IsValid() == false) || (bFireDelayTimerExpired))
	{
		GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &UShotgunProjectileComponent::TimerExpired, FireRate);
		bFireDelayTimerExpired = false;
	}
}

void UShotgunProjectileComponent::TimerExpired()
{
	bFireDelayTimerExpired = true;
}
