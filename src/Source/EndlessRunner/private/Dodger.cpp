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

void ADodger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Check if the other actor is a valid actor
	if (!OtherActor || OtherActor == this) return;
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
void ADodger::MoveRL(float Value)
{
	FString ValueStr = FString::SanitizeFloat(Value);
	if (!Moved && Value != 0)
	{
		startingPos = GetActorLocation();
		Position += Value;
		if (Position < -GridSlots) Position = -GridSlots;
		else if (Position > GridSlots) Position = GridSlots;

		if (CheckNearMiss()) Spawner->ReportNearMiss();

		SetActorLocation(FVector(startingPos.X, GridDistance * Position, startingPos.Z));
		Spawner->ReportPosition(Position);

		Moved = true;
	}
	else if (Value == 0)
	{
		Moved = false;
	}
}
bool ADodger::CheckNearMiss()
{
	UWorld* World = GetWorld();



	FVector RayStart = GetActorLocation();
	FVector RayEnd = RayStart + (FVector(1, 0, 0) * NearMissDistance);

	// Define the collision channel and trace parameters
	ECollisionChannel CollisionChannel = ECC_Visibility;
	FCollisionQueryParams TraceParams(TEXT("Raycast"), true, this);
	FHitResult HitResult;
	return World->LineTraceSingleByChannel(HitResult, RayStart, RayEnd, CollisionChannel, TraceParams);
}

