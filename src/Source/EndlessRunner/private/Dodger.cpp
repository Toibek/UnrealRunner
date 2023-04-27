// Fill out your copyright notice in the Description page of Project Settings.


#include "Dodger.h"
#include "Spawner.h"



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
		startingPos = GetActorLocation();
		Position += Value;
		if (Position < -GridSlots) Position = -GridSlots;
		else if (Position > GridSlots) Position = GridSlots;

		SetActorLocation(FVector(startingPos.X, GridDistance * Position, startingPos.Z));
		Spawner->ReportPosition(Position);

		Moved = true;
	}
	else if (Value == 0)
	{
		Moved = false;
	}
}
void ADodger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Check if the other actor is a valid actor
	if (OtherActor && OtherActor != this)
	{
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
}

