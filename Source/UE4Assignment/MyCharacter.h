// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "MyCharacter.generated.h"

class AWeaponBase;
UCLASS()
class UE4ASSIGNMENT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vectors")
		FVector ActorPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vectors")
		FRotator ActorRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Components")
		USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Components")
		bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Vectors")
		FVector MousePos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vectors")
		FVector WorldMousePosition;

	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
		class USpringArmComponent* CameraBoom;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		int InventorySize = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<AWeaponBase*> WeaponInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		float RayTraceZOffset = -80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
		float InteractRayTraceLength = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		AWeaponBase* CurrentWeapon;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MouseTrace(FVector CameraPosition, FVector MouseDirection);

	void MoveForward(float Axis);

	void MoveRight(float Axis);

	void Interact();

	void EquipWeapon(AWeaponBase* Weapon);

	void StartFire();
	void EndFire();
	void Reload();

private:

	AActor* FocusedActor;

	APlayerController* PlayerController;

};
