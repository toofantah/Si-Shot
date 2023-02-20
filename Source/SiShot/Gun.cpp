// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh -> SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult Hit;
	FVector ShotDir;
	bool Sucess = GunTrace(Hit, ShotDir);
	//Add Impact Effect
	if(Sucess)
	{
		//Spawn Emitter
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShotDir.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),ImpactSound,Hit.Location);
		AActor* HitActor = Hit.GetActor();
		if(HitActor != nullptr)
		{
			//Damage
			AController* OwnerContr = GetOwnerController();
			FPointDamageEvent DamageEvent(DamageAmount, Hit, ShotDir, nullptr);
			HitActor -> TakeDamage(DamageAmount, DamageEvent, OwnerContr, this);
		}

	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerContr = GetOwnerController();
	if(OwnerContr == nullptr) return false;
	FVector Location;
	FRotator Rotation;
	OwnerContr -> GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	//Calculate Hit Direction
	FVector EndPoint = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams Prams;
	Prams.AddIgnoredActor(this); //ignoring gun
	Prams.AddIgnoredActor(GetOwner());// ignoring Owner of the gun
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Prams);
}

AController* AGun::GetOwnerController() const
{
	//Get Controller from Owner Pawn
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
}

