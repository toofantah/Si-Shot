// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SiShotGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SISHOT_API ASiShotGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* Pawn);
};
