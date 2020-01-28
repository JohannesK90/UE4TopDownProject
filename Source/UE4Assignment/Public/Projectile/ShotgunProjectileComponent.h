// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include <TimerManager.h>

#include "ShotgunProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4ASSIGNMENT_API UShotgunProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShotgunProjectileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FireTimerHandle;
	FTimerHandle FireDelayTimerHandle;
	FTimerDelegate Delegate;
	bool bFireDelayTimerExpired = true;

public:	

	UFUNCTION(BlueprintCallable, Category = "Projectile", Meta = (ToolTip = "FireRate - Second between projectiles, NumOfBullets - How many bullets do you want to fire at once?, MaxFireAngle - Projectile will be fired within this angle. Shooting direction +- angle/2, DrawDebugLine - check if you want to see line when projectile moves"))
		void StartFire(float BulletSpeed = 1000.0f, float FireRate = 1.0f, float NumOfBullets = 8.0f, float BulletRange = 400.0f, float MaxFireAngle = 20.0f, bool bDrawDebugLine = true);

	UFUNCTION()
		void Fire(float BulletSpeed, float FireRate, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine);

	UFUNCTION(BlueprintCallable, Category = "Projectile", Meta = (ToolTip = "This stops auto fire timer."))
		void EndFire();

	UFUNCTION()
		void FireDelayTimer(float FireRate);

	UFUNCTION()
		void TimerExpired();

};
