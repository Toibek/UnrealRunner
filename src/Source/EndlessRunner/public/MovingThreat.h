// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingThreat.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMovingThreat : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingThreat();
	UPROPERTY(EditAnywhere, Category = "Moving")
		float MoveSpeed = 100;
	UPROPERTY(EditAnywhere, Category = "Moving")
		float MoveDistance = 20000;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector startingPos;
	float movedDistance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
