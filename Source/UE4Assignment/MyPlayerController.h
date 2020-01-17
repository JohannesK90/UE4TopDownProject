// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4ASSIGNMENT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
		AMyPlayerController();
public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vectors")
		FVector MousePos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vectors")
		FVector MouseDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vectors")
		FHitResult TraceHitResult;

};
