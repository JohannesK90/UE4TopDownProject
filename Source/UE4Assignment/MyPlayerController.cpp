// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::Tick(float DeltaTime)
{
	

	//Grab tha pawn actor form the player Character.
	if (auto Char = Cast<AMyCharacter>(GetPawn()))
	{
		DeprojectMousePositionToWorld(MousePos, MouseDir);

		Char->MouseTrace(MousePos, MouseDir);

		UKismetSystemLibrary::DrawDebugPoint
		(
			this,
			MousePos,
			3.0F,
			FLinearColor::Red,
			0.0f
		);

		UKismetSystemLibrary::DrawDebugArrow
		(
			this,
			MousePos,
			MousePos + MouseDir * 300.0f,
			3.0F,
			FLinearColor::Red,
			0.0f
		);

		/*This retruns a Vector position from under the mouse in the world.
		GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, true, TraceHitResult);
		We call the MouseTrace function and pass on the Vector position.
		DeprojectScreenPositionToWorld(ScreenXPos, ScreenYPos, MousePosHit1, MousePosHit2);*/
	}

}
