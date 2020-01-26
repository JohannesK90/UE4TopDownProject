// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4AssignmentGameMode.h"
#include "UE4AssignmentPlayerController.h"
#include "UE4AssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include <Blueprint/UserWidget.h>

void AUE4AssignmentGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUDClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

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