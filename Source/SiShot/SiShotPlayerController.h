// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SiShotPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SISHOT_API ASiShotPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:

	UPROPERTY(EditAnywhere) TSubclassOf<class UUserWidget> LoosScreenClass;
	UPROPERTY(EditAnywhere) TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere) float RestartDelay = 5;
	FTimerHandle ResetTimer;
};
