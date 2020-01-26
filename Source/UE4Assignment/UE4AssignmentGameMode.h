// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UE4AssignmentGameMode.generated.h"

UCLASS(minimalapi)
class AUE4AssignmentGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	AUE4AssignmentGameMode();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

};



