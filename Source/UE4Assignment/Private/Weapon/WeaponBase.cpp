// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Weapon/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetCollisionProfileName(TEXT("BlockAll"));
	WeaponMesh->SetSimulatePhysics(true);
	RootComponent = WeaponMesh;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = AmmoClip;
}

void AWeaponBase::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("On Interact"));
}
 
void AWeaponBase::StartFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Focus : %s"), *this->GetName());
}

void AWeaponBase::EndFocus_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Focus : %s"), *this->GetName());
}

void AWeaponBase::SetSimulatePhysics(bool value)
{
	WeaponMesh->SetSimulatePhysics(value);
}

void AWeaponBase::StartFire_Implementation()
{
}

void AWeaponBase::EndFire_Implementation()
{}

void AWeaponBase::Reload()
{
	if (AmmoPool <= 0 || CurrentAmmo >= AmmoClip)
	{
		return;
	}

	if (AmmoPool < (AmmoClip - CurrentAmmo))
	{
		CurrentAmmo += AmmoPool;
		AmmoPool = 0;
	}
	else
	{
		AmmoPool -= AmmoClip - CurrentAmmo;
		CurrentAmmo = AmmoClip;
	}

	if (ReloadSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ReloadSound, this->GetActorLocation());
	}
}