// Fill out your copyright notice in the Description page of Project Settings.


#include "SiShotPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void ASiShotPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD -> AddToViewport();
    }
}

void ASiShotPlayerController::GameHasEnded(class AActor* EndGameFocus, bool IsWinner)
{
    Super::GameHasEnded(EndGameFocus,IsWinner);
    HUD->RemoveFromViewport();
    if(IsWinner)
    {

        UUserWidget* WScreen = CreateWidget(this, WinScreenClass);
        if(WScreen != nullptr)
        {
            WScreen -> AddToViewport();
        }

    }
    else
    {

        UUserWidget* LScreen = CreateWidget(this, LoosScreenClass);
        if(LScreen != nullptr)
        {
            LScreen -> AddToViewport();
        }
    }
 
    GetWorldTimerManager().SetTimer(ResetTimer, this, &APlayerController::RestartLevel, RestartDelay);
}


