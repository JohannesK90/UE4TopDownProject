// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact/InteractInterface.h"
#include "Projectile/Projectile.h"

#include <Components/SkeletalMeshComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>
#include <Particles/ParticleSystem.h>

#include "WeaponBase.generated.h"

UCLASS()
class UE4ASSIGNMENT_API AWeaponBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Info|Mesh")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Info|Projectile")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Info|Ammo")
		bool bIsReloading = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|Ammo")
		int32 AmmoClip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|Ammo")
		int32 AmmoPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Info|Ammo")
		int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX")
		USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX")
		USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX")
		UParticleSystem* FireEffect;

protected:
	virtual void BeginPlay() override;


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void StartFocus();
	void StartFocus_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
		void EndFocus();
	void EndFocus_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void StartFire();
	virtual void StartFire_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void EndFire();
	virtual void EndFire_Implementation();

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void SetSimulatePhysics(bool value);
};
