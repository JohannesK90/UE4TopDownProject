// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VFX.h"

#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "../MyCharacter.h"

#include "Projectile.generated.h"

UCLASS()
class UE4ASSIGNMENT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	AMyCharacter* Player;

public:	

	// Sphere collision component.
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
		USphereComponent* CollisionComponent;
	
	// Sphere collision component.
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float CollisionRadius = 5.0f;

	// Projectile movement component.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
		UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		class UVFX* ParticleSystem;

public:

	UFUNCTION()
	void SetupMovement(float InitialSpeed, float MaxSpeed, float BulletRange);

	// Function that initializes the projectile's velocity in the shoot direction.
	UFUNCTION()
	void FireInDirection(const FVector& ShootDirection);

	// Function that is called when the projectile hits something.
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
