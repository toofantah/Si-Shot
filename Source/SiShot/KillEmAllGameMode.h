// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SiShotGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SISHOT_API AKillEmAllGameMode : public ASiShotGameModeBase
{
	GENERATED_BODY()
public:

	virtual void PawnKilled(APawn* Pawn)override;

private:

	void EndGame(bool HasPlayerWon);
};
