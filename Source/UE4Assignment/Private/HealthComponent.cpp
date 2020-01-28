// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	Health = DefaultHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		//NOTE::Something Is wrong here and I don't know what.
		//Owner->OnTakePointDamage.AddDynamic(this, &UHealthComponent::TakeDamge);
	}

}

void UHealthComponent::Heal(float HealValue)
{
	Health =+HealValue;
}

void UHealthComponent::TakeDamge
(
	AActor* DamageCauser, float Damage,
	FVector HitLocation, class UPrimitiveComponent*
	FHitComponent, FVector ShotFromDirection
)
{

	if (Damage <= 0)
	{
		return;
	}
	//Clamp health from 0 to "DefaultHealth".
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

}

