// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SoldierAiController.h"

void AKillEmAllGameMode::PawnKilled(APawn* Pawn)
{
    Super::PawnKilled(Pawn);
    APlayerController* PlayerContr = Cast<APlayerController>(Pawn->GetController());

    if(PlayerContr != nullptr){
        EndGame(false);
    }

    // TODO: 
    // Loop through each AIs and check If they are alive
    for(ASoldierAiController* ctr : TActorRange<ASoldierAiController>(GetWorld())){
        if(!ctr->IsDead()) return;
    }
    
    EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool HasPlayerWon)
{
    for(AController* Contr : TActorRange<AController>(GetWorld()))
    {
        bool IsWinner = Contr -> IsPlayerController() == HasPlayerWon;
        Contr -> GameHasEnded(Contr->GetPawn(), IsWinner);
    }
}
