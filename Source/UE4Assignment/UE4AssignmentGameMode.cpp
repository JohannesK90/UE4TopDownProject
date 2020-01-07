// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4AssignmentGameMode.h"
#include "UE4AssignmentPlayerController.h"
#include "UE4AssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4AssignmentGameMode::AUE4AssignmentGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE4AssignmentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}