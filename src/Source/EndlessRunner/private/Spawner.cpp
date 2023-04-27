// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

ASpawner* ASpawner::Instance = nullptr;
// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
void ASpawner::PreInitializeComponents()
{
	// Perform initialization tasks here

	Instance = this;
	UE_LOG(LogTemp, Log, TEXT("Instance has been set"));

	Super::PreInitializeComponents();


}
// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnActor();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayTime += DeltaTime;
	SpawnRate = SpawnRateCurve.GetRichCurveConst()->Eval(PlayTime);
	Speed = SpeedCurve.GetRichCurveConst()->Eval(PlayTime);


	SpawnTimer += DeltaTime;
	if (SpawnTimer >= 1 / SpawnRate)
	{
		SpawnActor();
		SpawnTimer = 0.0f;
	}
	FVector speed(-Speed * DeltaTime, 0, 0);
	int Length = MovingObjects.Num();
	for (int i = Length - 1; i >= 0; i--)
	{
		AActor* actor = MovingObjects[i];
		FVector aPos = actor->GetActorLocation();
		if (aPos.X < -TravelDistance)
		{
			MovingObjects.Remove(actor);
			actor->SetActorLocation(FVector(SpawnDistance, aPos.Y, SpawnHeight));
			IdleObjects.Add(actor);
		}
		else
			actor->SetActorLocation(aPos + speed);
	}

}
ASpawner* ASpawner::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<ASpawner>();
	}
	return Instance;
}
void ASpawner::ReportPosition(int val)
{
	LastPosition = val;
}
int ASpawner::GetSlots()
{
	return GridSlots;
}
float ASpawner::GetDistance()
{
	return GridDistance;
}
void ASpawner::SpawnActor()
{
	int Length = IdleObjects.Num();

	int rand = FMath::RandRange(LastPosition - 1, LastPosition + 1);
	if (rand < -GridSlots) rand = -GridSlots;
	else if (rand > GridSlots) rand = GridSlots;

	if (Length > 0)
	{
		AActor* actor = IdleObjects[0];
		actor->SetActorLocation(GetActorLocation() + FVector(SpawnDistance, rand * GridDistance, SpawnHeight));
		IdleObjects.Remove(actor);
		MovingObjects.Add(actor);
	}
	else
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		AActor* spawned = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation() + FVector(SpawnDistance, rand * GridDistance, SpawnHeight), GetActorRotation(), SpawnParams);
		MovingObjects.Add(spawned);
	}
}

