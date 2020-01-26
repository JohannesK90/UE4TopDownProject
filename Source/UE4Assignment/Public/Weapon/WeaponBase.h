// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interact/InteractInterface.h"
#include "../MyCharacter.h"
#include "BulletProjectile.h"

#include "WeaponBase.generated.h"

UCLASS()
class UE4ASSIGNMENT_API AWeaponBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
		USceneComponent* WeaponMuzzle;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABulletProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool bIsReloading = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool bAutomaticFire = false;

	//ammo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
		int32 AmmoClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
		int32 AmmoPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon|Ammo")
		int32 CurrentAmmo;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	
	
	FTimerHandle AutomaticFireHandle;

	bool bExuteActive = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void FireBullet(float Velocity = 1.0f, float RateOfFire = 0.0f, float RecoilForce = 0.0f, float BulletRange = 1200.0f);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void FireLineTrace(float RateOfFire, float RecoilForce, float BulletRange);
};
