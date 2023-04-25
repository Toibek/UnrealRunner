// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Dodger.generated.h"

UCLASS()
class ENDLESSRUNNER_API ADodger : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADodger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "World")
		int GridSlots = 1;

	UPROPERTY(EditAnywhere, Category = "World")
		float GridDistance = 2;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveRL(float Value);
	int Position = 0;
	bool Moved = false;
};
