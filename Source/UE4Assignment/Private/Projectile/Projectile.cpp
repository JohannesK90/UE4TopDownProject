// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(CollisionRadius);
	// Set the root component to be the collision component.
	RootComponent = CollisionComponent;

	// Use this component to drive this projectile's movement.
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);

	ParticleSystem = CreateDefaultSubobject<UVFX>(TEXT("ParticleImpact"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::SetupMovement(float Velocity, float BulletRange)
{
	ProjectileMovementComponent->InitialSpeed = Velocity * 1000.f;
	ProjectileMovementComponent->MaxSpeed = Velocity * 1000.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	InitialLifeSpan = BulletRange / ProjectileMovementComponent->MaxSpeed;
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	HitComponent->SetSimulatePhysics(true);
	float Mass = HitComponent->GetMass();
	HitComponent->SetSimulatePhysics(false);
	FVector Force = GetVelocity() * Mass;
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComponent != NULL) && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(Force, GetActorLocation());
	}
	ParticleSystem->SpawnParticle(Hit.Location, FRotator::ZeroRotator);
	Destroy();
}

