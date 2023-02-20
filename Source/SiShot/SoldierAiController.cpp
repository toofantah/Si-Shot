// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Soldier.h"
void ASoldierAiController::BeginPlay()
{
    Super::BeginPlay();
    AiBehvaior = LoadObject<UBehaviorTree>(nullptr, TEXT("/Game/Blueprints/Character/Ai/BT_Enemy_Ai"));

    if(AiBehvaior != nullptr) 
    {
        RunBehaviorTree(AiBehvaior);
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

    }else{
        UE_LOG(LogTemp, Warning, TEXT("No Behvior Tree"));
    }
}

void ASoldierAiController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

bool ASoldierAiController::IsDead() const
{
    //Check the Pawn and return if its dead
    ASoldier* Soldier = Cast<ASoldier>(GetPawn());
    if(Soldier != nullptr){
        return Soldier->IsDead();
    }
    return true;
}
    




