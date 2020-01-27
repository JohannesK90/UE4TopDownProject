// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include <TimerManager.h>

#include "SingleFireProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4ASSIGNMENT_API USingleFireProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USingleFireProjectileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FireTimerHandle;
	FTimerHandle FireDelayTimerHandle;
	FTimerDelegate Delegate;
	bool bFireDelayTimerExpired = true;

public:	

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void StartFire(float Velocity, float FireRate, float BulletRange, float RecoilMaxAngle, bool bDrawDebugLine);

	UFUNCTION()
		void Fire(float Velocity, float FireRate, float BulletRange, float RecoilMaxAngle, bool bDrawDebugLine);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void EndFire();

	UFUNCTION()
		void FireDelayTimer(float FireRate);

	UFUNCTION()
		void TimerExpired();
};
