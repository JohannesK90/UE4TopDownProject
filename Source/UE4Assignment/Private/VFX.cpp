// Fill out your copyright notice in the Description page of Project Settings.


#include "VFX.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UVFX::UVFX()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UVFX::BeginPlay()
{
	Super::BeginPlay();

}

//Spawn a new VFX at location
void UVFX::SpawnParticle(FVector Location, FRotator Rotation)
{
	UParticleSystemComponent* SpawnedParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, Location, Rotation);
}


// Called every frame
void UVFX::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

