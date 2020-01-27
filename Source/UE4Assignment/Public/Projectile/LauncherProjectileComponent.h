// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include <TimerManager.h>

#include "LauncherProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4ASSIGNMENT_API ULauncherProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULauncherProjectileComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FireTimerHandle;
	FTimerHandle FireDelayTimerHandle;
	FTimerDelegate Delegate;
	bool bFireDelayTimerExpired = true;

public:	

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void StartFire(float InitialSpeed = 500.0f, float MaxSpeed = 1000.0f, float FireRate = 1.5f, float BulletRange = 1200.0f, float RecoilMaxAngle = 25.0f, bool bDrawDebugLine = true);

	UFUNCTION()
		void Fire(float InitialSpeed, float MaxSpeed, float FireRate, float BulletRange, float RecoilMaxAngle, bool bDrawDebugLine);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void EndFire();

	UFUNCTION()
		void FireDelayTimer(float FireRate);

	UFUNCTION()
		void TimerExpired();
		
};
