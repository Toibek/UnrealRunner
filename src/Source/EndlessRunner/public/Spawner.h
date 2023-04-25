// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<class AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float SpawnRate = 1;

	UPROPERTY(EditAnywhere, Category = "World")
		int GridSlots = 1;

	UPROPERTY(EditAnywhere, Category = "World")
		float GridDistance = 2;


protected:
	float SpawnTimer; // Added SpawnTimer as a protected member variable
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void SpawnActor();

};
