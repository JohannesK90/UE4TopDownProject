// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/Projectile.h"
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundBase.h>
#include "Weapon/WeaponBase.h"

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

	Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AProjectile::SetupMovement(float InitialSpeed, float MaxSpeed, float BulletRange)
{
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	InitialLifeSpan = BulletRange / ProjectileMovementComponent->MaxSpeed;
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	if (Player->CurrentWeapon->FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Player->CurrentWeapon->FireSound, this->GetActorLocation());
	}
	if (Player->CurrentWeapon->FireEffect)
	{
		FTransform MuzzleTransform = Player->CurrentWeapon->WeaponMesh->GetSocketTransform("muzzle");
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Player->CurrentWeapon->FireEffect, MuzzleTransform);
	}
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
		// if the hit object got physics enable, then we add some force depending of the bullets velocity and mass
		OtherComponent->AddImpulseAtLocation(Force, GetActorLocation());
	}
	if (OtherComponent->ComponentHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy hit"));
		AWeaponBase* Weapon = Cast<AWeaponBase>(Player->CurrentWeapon);
		UGameplayStatics::ApplyPointDamage(OtherActor, Weapon->Damage, Hit.Location, Hit, Player->GetInstigatorController(), Player, nullptr);
	}

	// Spawn VFX particle at the hit location
	ParticleSystem->SpawnParticle(Hit.Location, FRotator::ZeroRotator);

	Destroy();
}

