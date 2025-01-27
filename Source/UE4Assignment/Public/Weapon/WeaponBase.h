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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Info|Mesh", Meta = (ToolTip = "Weapon Mesh."))
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Info|Projectile", Meta = (ToolTip = "When firing the weapon, this projectile will be fired."))
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Info|Ammo")
		bool bIsReloading = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info")
		float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|Ammo", Meta = (ToolTip = "Ammo amount in a clip."))
		int32 AmmoClip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|Ammo", Meta = (ToolTip = "Extra ammo that this weapon can use."))
		int32 AmmoPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Info|Ammo")
		int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX", Meta = (ToolTip = "When firing the weapon, this sound will be played."))
		USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX", Meta = (ToolTip = "When reloading the weapon, this sound will be played."))
		USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Info|SFX/VFX", Meta = (ToolTip = "When the weapon's bullet hits enemy, this effect will be shown."))
		UParticleSystem* FireEffect;

protected:
	virtual void BeginPlay() override;


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction", Meta = (ToolTip = "This Evene is called when 'F' key is pressed."))
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction", Meta = (ToolTip = "This Event is called when the player's interact line trace touches this object."))
		void StartFocus();
	void StartFocus_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction", Meta = (ToolTip = "This Event is called when the player's interact line trace stops touching this object."))
		void EndFocus();
	void EndFocus_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon", Meta = (ToolTip = "This Event is called when the player has a weapon and 'Mouse Left' button is pressed."))
		void StartFire();
	virtual void StartFire_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon", Meta = (ToolTip = "This Event is called when the player has a weapon and 'Mouse Left' button is released."))
		void EndFire();
	virtual void EndFire_Implementation();

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void SetSimulatePhysics(bool value);
};
