// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"



// Sets default values
ASoldier::ASoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	Gun = GetWorld()-> SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); 
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_rSocket"));
	Gun->SetOwner(this);
}

bool ASoldier::IsDead() const
{
	return Health <= 0;
}

// Called every frame
void ASoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASoldier::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float TakenDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float DamageToApply = FMath::Min(Health, TakenDamage);
	Health -= DamageToApply;
	if(IsDead()){
		DetachFromControllerPendingDestroy(); // Detaching Controller
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Deactivating Capusle Colision
	}
	return Health;
}

// Called to bind functionality to input
void ASoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ASoldier::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &ASoldier::MoveSide);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &ASoldier::LookRightRate);
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &ASoldier::LookUpRate);


	PlayerInputComponent -> BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this,&ACharacter::Jump);
	PlayerInputComponent -> BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this,&ASoldier::Shoot);

}

void ASoldier::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASoldier::MoveSide(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASoldier::LookUpRate(float AxisValue)
{
	AddControllerPitchInput( AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}

void ASoldier::LookRightRate(float AxisValue)
{
	AddControllerYawInput( AxisValue * RotationRate * GetWorld() -> GetDeltaSeconds());
}

void ASoldier::Shoot()
{
	Gun -> PullTrigger();
}
