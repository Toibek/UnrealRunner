
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Spawner.h"
#include "Dodger.generated.h"

UCLASS()
class ENDLESSRUNNER_API ADodger : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADodger();

	UPROPERTY(EditAnywhere)
		int Lives = 3;
	UPROPERTY(EditAnywhere)
		float NearMissDistance;

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* other) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveRL(float Value);
	bool CheckNearMiss();

	int Position = 0;
	bool Moved = false;
	ASpawner* Spawner;
	int GridSlots = 1;
	float GridDistance = 2;
	FVector startingPos;
};
