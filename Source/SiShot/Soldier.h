// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Soldier.generated.h"

class AGun;

UCLASS()
class SISHOT_API ASoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoldier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Shoot();

	UPROPERTY(EditAnywhere) float RotationRate = 100;
	UPROPERTY(EditDefaultsOnly) float MaxHealth = 100;
	UPROPERTY(VisibleAnywhere) float Health;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AGun> GunClass;
	UPROPERTY() AGun* Gun;
};
