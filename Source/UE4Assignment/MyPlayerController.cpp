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
		//This retruns a Vector position from under the mouse in the world.
		DeprojectMousePositionToWorld(MousePos, MouseDir);

		//Send the mouse position to the character class.
		Char->MouseTrace(MousePos, MouseDir);
	}

}
