// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingThreat.h"

// Sets default values
AMovingThreat::AMovingThreat()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingThreat::BeginPlay()
{
	Super::BeginPlay();
	startingPos = GetActorLocation();
}

// Called every frame
void AMovingThreat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	movedDistance += MoveSpeed * DeltaTime;
	SetActorLocation(startingPos + FVector(-movedDistance, 0, 0));

	if (movedDistance > MoveDistance)
		Destroy();
}

