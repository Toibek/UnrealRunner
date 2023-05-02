// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodger.h"
#include "Spawner.h"



// Sets default values
ADodger::ADodger()
{


}

// Called when the game starts or when spawned
void ADodger::BeginPlay()
{
	Super::BeginPlay();

	Spawner = ASpawner::GetInstance();
	if (Spawner)
	{
		GridSlots = Spawner->GetSlots();
		GridDistance = Spawner->GetDistance();
		Spawner->ReportAlive();
	}
	else
		UE_LOG(LogTemp, Log, TEXT("Kringe, spawner not found"));

}


void ADodger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Check if the other actor is a valid actor
	if (!OtherActor || OtherActor == this) return;
	Lives--;
	if (Lives < 0)
	{
		Spawner->ReportDeath();
		Destroy();
	}
	else
	{
		Spawner->ReportHit(OtherActor);
		UE_LOG(LogTemp, Warning, TEXT("Collision Begin! %d Lives left!"), Lives);
	}
}
void ADodger::MoveRL(float Value)
{
	startingPos = GetActorLocation();
	Position += Value;
	if (Position < -GridSlots) Position = -GridSlots;
	else if (Position > GridSlots) Position = GridSlots;

	if (CheckNearMiss()) Spawner->ReportNearMiss();

	SetActorLocation(FVector(startingPos.X, GridDistance * Position, startingPos.Z));
	Spawner->ReportPosition(Position);
}
bool ADodger::CheckNearMiss()
{
	UWorld* World = GetWorld();



	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (FVector(1, 0, 0) * NearMissDistance);

	// Define the collision channel and trace parameters
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionQueryParams TraceParams(TEXT("Raycast"), true, this);
	FHitResult HitResult;
	World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, CollisionChannel, TraceParams);
	AActor* HitActor = HitResult.GetActor();
	if (HitActor)
	{
		FString ActorName = HitActor->GetName();
		return(!ActorName.Contains(FString(TEXT("ADodgerBot"))));
	}
	return false;
}

