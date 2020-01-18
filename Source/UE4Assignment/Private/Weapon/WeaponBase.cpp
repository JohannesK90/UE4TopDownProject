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
	UE_LOG(LogTemp, Warning, TEXT("Start Focus"));
}

void AWeaponBase::EndFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Focus"));
}

