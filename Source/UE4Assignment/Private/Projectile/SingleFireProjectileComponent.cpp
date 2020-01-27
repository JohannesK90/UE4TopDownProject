// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/SingleFireProjectileComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Weapon/WeaponBase.h"
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Engine/World.h>
#include <Engine/Engine.h>

// Sets default values for this component's properties
USingleFireProjectileComponent::USingleFireProjectileComponent()
{}

// Called when the game starts
void USingleFireProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USingleFireProjectileComponent::StartFire(float Velocity, float FireRate, float BulletRange, float RecoilMaxAngle, bool bDrawDebugLine)
{
	Delegate.BindUObject(this, &USingleFireProjectileComponent::Fire, Velocity, FireRate, BulletRange, RecoilMaxAngle, bDrawDebugLine);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, Delegate, FireRate, true, 0.0f);
}

void USingleFireProjectileComponent::Fire(float Velocity, float FireRate, float BulletRange, float RecoilMaxAngle, bool bDrawDebugLine)
{
	if (bFireDelayTimerExpired)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(GetOwner());

		if (!Weapon->ProjectileClass)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProjectileClass is null."));
			return;
		}

		if (Weapon->CurrentAmmo <= 0)
		{
			return;
		}
		Weapon->CurrentAmmo -= 1;

		// Spawn NumOfBullets at owner(weapon)'s muzzle
		FTransform MuzzleTransform = Weapon->WeaponMesh->GetSocketTransform("muzzle");
		FVector MuzzleLocation = MuzzleTransform.GetLocation();
		FRotator MuzzleRotation = MuzzleTransform.GetRotation().Rotator();

		// set random muzzle's rotation 
		FRotator RandomRotation = MuzzleRotation.Add(0.0f, FMath::RandRange(-RecoilMaxAngle / 2, RecoilMaxAngle / 2), 0.0f);
		MuzzleTransform.SetRotation(RandomRotation.Quaternion());

		// SpawnActorDeferred -> modify projectile's initialLifeSpan with BulletRange -> FinishSpawningActor
		AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(Weapon->ProjectileClass, MuzzleTransform);
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

		FireDelayTimer(FireRate);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
		Delegate.BindUObject(this, &USingleFireProjectileComponent::Fire, Velocity, FireRate, BulletRange, RecoilMaxAngle, bDrawDebugLine);
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, Delegate, FireRate, true, 0.0f);
	}
}

void USingleFireProjectileComponent::EndFire()
{
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void USingleFireProjectileComponent::FireDelayTimer(float FireRate)
{
	// If the timer has expired or does not exist, start it  
	if ((FireDelayTimerHandle.IsValid() == false) || (bFireDelayTimerExpired))
	{
		GetWorld()->GetTimerManager().SetTimer(FireDelayTimerHandle, this, &USingleFireProjectileComponent::TimerExpired, FireRate);
		bFireDelayTimerExpired = false;
	}
}

void USingleFireProjectileComponent::TimerExpired()
{
	bFireDelayTimerExpired = true;
}