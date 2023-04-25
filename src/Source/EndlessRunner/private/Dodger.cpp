// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodger.h"

// Sets default values
ADodger::ADodger()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADodger::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADodger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADodger::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveRL"), this, &ADodger::MoveRL);
}

void ADodger::MoveRL(float Value)
{
	FString ValueStr = FString::SanitizeFloat(Value);
	if (!Moved && Value != 0)
	{
		Position += Value;
		if (Position < -GridSlots) Position = -GridSlots;
		else if (Position > GridSlots) Position = GridSlots;
		SetActorLocation(FVector(0, GridDistance * Position, 100));

		UE_LOG(LogTemp, Log, TEXT("MoveRL: %s"), *ValueStr);
		Moved = true;
	}
	else if (Value == 0)
	{
		Moved = false;
	}
}
