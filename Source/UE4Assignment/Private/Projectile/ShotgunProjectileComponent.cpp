// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Assignment/Public/Projectile/ShotgunProjectileComponent.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Weapon/WeaponBase.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UShotgunProjectileComponent::UShotgunProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UShotgunProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UShotgunProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UShotgunProjectileComponent::Fire(float Velocity, float NumOfBullets, float BulletRange, float MaxFireAngle, bool bDrawDebugLine)
{
	if (!ProjectileClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProjectileClass is null. (ShotgunProjectileComponent -> ProjectileClass -> BP_Projectile)"));
		return;
	}

	AWeaponBase* Weapon = Cast<AWeaponBase>(GetOwner());

	FTransform MuzzleTransform = Weapon->WeaponMesh->GetSocketTransform("muzzle");
	FVector MuzzleLocation = MuzzleTransform.GetLocation();
	FRotator MuzzleRotation = MuzzleTransform.GetRotation().Rotator();

	UWorld* World = GetWorld();

	if (World)
	{
		for (int i = 0; i < NumOfBullets; i++)
		{			
			// set random muzzle's rotation 
			FRotator RandomRotation = MuzzleRotation.Add(0.0f, FMath::RandRange(-MaxFireAngle / 2, MaxFireAngle / 2), 0.0f);
			MuzzleTransform.SetRotation(RandomRotation.Quaternion());
			// random is weird.. maybe seed related problem??
			UE_LOG(LogTemp, Warning, TEXT("Random Rotation : %s"), *RandomRotation.ToString());

			// get projectile - modify initiallifespan - spawn
			// spawn -> modify initialLifespan causes lots of problem.
			AProjectile* Projectile = World->SpawnActorDeferred<AProjectile>(ProjectileClass, MuzzleTransform);
			Projectile->SetupMovement(Velocity, BulletRange);
			UGameplayStatics::FinishSpawningActor(Projectile, MuzzleTransform);

			FVector LaunchDirection = RandomRotation.Vector();
			Projectile->FireInDirection(LaunchDirection);
			
			// set the muzzle's rotation back to default
			MuzzleTransform.SetRotation(MuzzleRotation.Quaternion());

			if (bDrawDebugLine)
			{
				FVector Start = MuzzleLocation + MuzzleRotation.Vector();
				FVector End = MuzzleLocation + RandomRotation.Vector() * BulletRange;

				DrawDebugLine(
					GetWorld(),
					Start,
					End,
					FColor::Green,
					false,
					0.5f,
					0,
					0.0f
				);
			}
		}
	}

	//AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//AWeaponBase* Weapon = Cast<AWeaponBase>(Player->CurrentWeapon);
	//if (Weapon)
	//{
	//	if (!Weapon->bIsReloading)
	//	{

	//		FVector MuzzleLocation = Weapon->WeaponMesh->GetSocketLocation("muzzle");
	//		FRotator MuzzleRotation = Weapon->WeaponMesh->GetSocketRotation("muzzle");

	//		for (int i = 0; i < NumOfBullets; i++)
	//		{
	//			/*FRotator NewMuzzleRotation = MuzzleRotation.Add(0.0f, FMath::RandRange(-MaxFireAngle / 2, MaxFireAngle / 2), 0.0f);
	//			ABulletProjectile* Bullet = GetWorld()->SpawnActor<ABulletProjectile>(ProjectileClass, MuzzleLocation, NewMuzzleRotation);
	//			if (!Bullet)
	//			{
	//				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ProjectileClass is null."));
	//				return;
	//			}
	//			Bullet->SetupBullet(Velocity, BulletRange);
	//			UGameplayStatics::FinishSpawningActor(Bullet, Weapon->WeaponMesh->GetSocketTransform("muzzle"));

	//			FVector Start = MuzzleLocation + MuzzleRotation.Vector();
	//			FVector End = MuzzleLocation + NewMuzzleRotation.Vector() * BulletRange;

	//			DrawDebugLine(
	//				GetWorld(),
	//				Start,
	//				End,
	//				FColor::Green,
	//				false,
	//				0.5f,
	//				0,
	//				0.0f
	//			);*/
	//		}

	//	}
	//}
}
//
//void UShotgunProjectileComponent::Fire()
//{
//	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
//	AWeaponBase* Weapon = Cast<AWeaponBase>(Player->CurrentWeapon);
//	if (Weapon)
//	{
//		if (!Weapon->bIsReloading)
//		{
//			//FVector MuzzleLocation = Weapon->WeaponMesh->GetSocketLocation("muzzle");
//		}
//
//		//FVector Start = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Vector();
//		//FVector End = WeaponMuzzle->GetComponentLocation() + Player->GetViewRotation().Add(0.0f, FMath::RandRange(-RecoilForce, RecoilForce), 0.0f).Vector() * BulletRange;
//
//		//FRotator MouseDir = UKismetMathLibrary::FindLookAtRotation(Start, End);
//		//WeaponMuzzle->SetWorldRotation(MouseDir);
//
//		//ABulletProjectile* Bullet = GetWorld()->SpawnActorDeferred<ABulletProjectile>(ProjectileClass, WeaponMuzzle->GetComponentTransform());
//
//		//Bullet->SetupBullet(Velocity, BulletRange);
//		//UGameplayStatics::FinishSpawningActor(Bullet, WeaponMuzzle->GetComponentTransform());
//
//
//		//DrawDebugLine(
//		//	GetWorld(),
//		//	Start,
//		//	End,
//		//	FColor::Blue,
//		//	false,
//		//	0.5f,
//		//	0,
//		//	0.0f
//		//);
//}

