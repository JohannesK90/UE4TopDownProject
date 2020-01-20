// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interact/InteractInterface.h"
#include "Engine/DataTable.h"
#include "../MyCharacter.h"

#include "WeaponBase.generated.h"

USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere)
		class USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere)
		FString WeaponName;
};

UENUM(BlueprintType)
enum class EWeaponNameEnum : uint8
{
	AK47	UMETA(DisplayName = "AK47"),
	M4A1	UMETA(DisplayName = "M4A1"),
};

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
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
		bool bIsReloading = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
		class UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		EWeaponNameEnum WeaponNameEnum;

	FWeaponData* WeaponData;

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

	void SetSimulatePhysics();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void StartFire();
	virtual void StartFire_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void EndFire();
	virtual void EndFire_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
		void Reload();
	virtual void Reload_Implementation();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void FireBullet(float Velocity = 1.0f, float RateOfFire = 0.0f, float RecoilForce = 0.0f);

};
