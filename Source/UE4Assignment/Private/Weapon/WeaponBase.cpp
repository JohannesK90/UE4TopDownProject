// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	RootComponent = WeaponMesh;

	if (WeaponMuzzle == nullptr)
	{
		WeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
		WeaponMuzzle->SetupAttachment(WeaponMesh);
	}


}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponDataTable)
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponNameEnum"), true);

		UE_LOG(LogTemp, Warning, TEXT("Start Focus : %s"), *EnumPtr->GetDisplayValueAsText(WeaponNameEnum).ToString());
		WeaponData = WeaponDataTable->FindRow<FWeaponData>(*EnumPtr->GetDisplayValueAsText(WeaponNameEnum).ToString(), FString(""), true);
		if (WeaponData)
		{
			WeaponMesh->SetSkeletalMesh(WeaponData->WeaponMesh);
			WeaponMesh->SetCollisionProfileName(TEXT("BlockAll"));
			WeaponMesh->SetSimulatePhysics(true);
		}
	}
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("On Interact"));

	//Destroy();
}
 
void AWeaponBase::StartFocus_Implementation()
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponNameEnum"), true);
	UE_LOG(LogTemp, Warning, TEXT("Start Focus : %s"), *EnumPtr->GetDisplayValueAsText(WeaponNameEnum).ToString());
}

void AWeaponBase::EndFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Focus"));
}

void AWeaponBase::SetSimulatePhysics(bool value)
{
	WeaponMesh->SetSimulatePhysics(value);
}

void AWeaponBase::StartFire_Implementation()
{
	if (!bIsReloading)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::StartFire()"));
	}
}

void AWeaponBase::EndFire_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::EndFire() "));
}

void AWeaponBase::Reload_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetName() + TEXT(" - AWeaponBase::Reload() "));
}

void AWeaponBase::FireBullet(float Velocity, float RateOfFire, float RecoilForce)
{
	if (!bIsReloading)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AWeaponBase::FireBullet"));
	}
}

