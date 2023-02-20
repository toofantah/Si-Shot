// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

void ASoldierAiController::BeginPlay()
{
    Super::BeginPlay();
    AiBehvaior = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/Blueprints/Character/Ai/BT_Enemy_Ai"));

    if(AiBehvaior != nullptr) 
    {
        
        // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        RunBehaviorTree(AiBehvaior);
        // GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

    }else{
        UE_LOG(LogTemp, Warning, TEXT("No Behvior Tree"));
    }
}

void ASoldierAiController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
        if(AiBehvaior != nullptr) 
    {
        
        // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        RunBehaviorTree(AiBehvaior);
        // GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

    }else{
        UE_LOG(LogTemp, Warning, TEXT("No Behvior Tree"));
    }
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if(PlayerPawn != nullptr)
    {
        UBlackboardComponent* MyBlackboard = GetBlackboardComponent();
        if(MyBlackboard)
        {
            if(LineOfSightTo(PlayerPawn))
          {
            if (MyBlackboard->GetKeyID("PlayerLocation") != -1) MyBlackboard->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
            if (MyBlackboard->GetKeyID("LastKnownPlayerLocation") != -1) MyBlackboard->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
        
          }
        else
        {
            if (MyBlackboard->GetKeyID("PlayerLocation") != -1) MyBlackboard->ClearValue(TEXT("PlayerLocation"));;
       
        }  
        }else{
            //  UE_LOG(LogTemp, Warning, TEXT("Not Found!"));
        }
    }

}


