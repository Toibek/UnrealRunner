// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgerBot.h"

ADodgerBot::ADodgerBot()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called every frame
void ADodgerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ThinkTimer += DeltaTime;
	if (ThinkTimer >= ThinkTime)
	{
		ThinkTimer = 0;
		Think();
	}
}
void ADodgerBot::Think()
{

	//UE_LOG(LogTemp, Warning, TEXT("Thinking"));
	UWorld* World = GetWorld();
	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (FVector(1, 0, 0) * SightDistance);

	// Define the collision channel and trace parameters
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionQueryParams TraceParams(TEXT("Raycast"), true, this);
	FHitResult HitResult;

	if (World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, CollisionChannel, TraceParams))
	{
		int rand = FMath::RandRange(-1, 1);
		if (rand != 0)
			MoveRL(rand);
	}
}
