// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Implement the spawning logic based on SpawnRate, if desired
	// For example, you can use a timer to spawn actors at a specific rate
	// or trigger the spawning logic based on certain conditions

	// Spawn actors at the specified SpawnRate
	SpawnTimer += DeltaTime;
	if (SpawnTimer >= SpawnRate)
	{
		SpawnActor();
		SpawnTimer = 0.0f;
	}
}

void ASpawner::SpawnActor()
{
	// Spawn the desired actor at the spawner's location and rotation
	FActorSpawnParameters SpawnParams;
	int rand = FMath::RandRange(-GridSlots, GridSlots);
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation() + FVector(0, rand * GridDistance, 0), GetActorRotation(), SpawnParams);
}

