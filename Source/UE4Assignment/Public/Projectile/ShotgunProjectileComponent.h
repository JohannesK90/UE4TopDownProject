// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"

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

public:	

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void Fire(float Velocity, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
		TSubclassOf<class AProjectile> ProjectileClass;
};
