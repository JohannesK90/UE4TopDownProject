// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);

	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;

	ParticleSystem = CreateDefaultSubobject<UVFX>(TEXT("ParticleImpact"));
}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ABulletProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	HitComp->SetSimulatePhysics(true);
	float Mass = HitComp->GetMass();
	HitComp->SetSimulatePhysics(false);
	FVector Force = GetVelocity() * Mass;
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		// if the hit object got physics enable, then we add some force depending of the bullets velocity and mass
		OtherComp->AddImpulseAtLocation(Force, GetActorLocation());
	}
	// Spawn VFX particle at the hit location
	ParticleSystem->SpawnParticle(Hit.Location, Hit.Actor->GetActorRotation());

	Destroy();
}

// Make sure the ProjectileMovement get the right values
void ABulletProjectile::SetupBullet(float Velocity, float Range)
{
	ProjectileMovement->InitialSpeed = Velocity * 1000.f;
	ProjectileMovement->MaxSpeed = Velocity * 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = Range / ProjectileMovement->MaxSpeed;
}
