// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponDataTable)
	{
		static const FString PString = FString("AK47DT"); // this is problem i think!!!
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EWeaponNameEnum"), true);
		WeaponData = WeaponDataTable->FindRow<FWeaponData>(*EnumPtr->GetDisplayValueAsText(WeaponNameEnum).ToString(), PString, true);
		if (WeaponData)
		{
			MeshComp->SetSkeletalMesh(WeaponData->WeaponMesh);
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

	// Todo: equip weapon

	Destroy();
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

