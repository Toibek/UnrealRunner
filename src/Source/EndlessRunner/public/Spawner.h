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
	UFUNCTION()
		static  ASpawner* GetInstance();
	UFUNCTION()
		float GetDistance();
	UFUNCTION()
		int GetSlots();
	UFUNCTION()
		void ReportPosition(int val);

	UPROPERTY(EditAnywhere, Category = "Spawner")
		TSubclassOf<class AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere, Category = "Spawner")
		float SpawnHeight;

	UPROPERTY(EditAnywhere, Category = "World")
		int GridSlots = 1;
	UPROPERTY(EditAnywhere, Category = "World")
		float GridDistance = 2;

	UPROPERTY(EditAnywhere, Category = "World")
		float SpawnDistance = 3500;
	UPROPERTY(EditAnywhere, Category = "World")
		float TravelDistance = 1000;

	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
		float PlayTime;
	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
		float SpawnRate = 1;
	UPROPERTY(EditAnywhere, Category = "Difficulty")
		FRuntimeFloatCurve SpawnRateCurve;
	UPROPERTY(VisibleAnywhere, Category = "Difficulty")
		float Speed = 10;
	UPROPERTY(EditAnywhere, Category = "Difficulty")
		FRuntimeFloatCurve SpeedCurve;



protected:
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	static ASpawner* Instance;
	int LastPosition;
	float SpawnTimer; // Added SpawnTimer as a protected member variable
	void SpawnActor();
	TArray<AActor*> MovingObjects;
	TArray<AActor*> IdleObjects;
};
