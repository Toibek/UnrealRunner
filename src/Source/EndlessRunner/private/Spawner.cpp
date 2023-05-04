// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Misc/FileHelper.h"

ASpawner* ASpawner::Instance = nullptr;
bool GameActive = true;
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
	GameActive = true;
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GameActive)
	{
		PlayTime += DeltaTime;
		SpawnRate = SpawnRateCurve.GetRichCurveConst()->Eval(PlayTime);
		Speed = SpeedCurve.GetRichCurveConst()->Eval(PlayTime);
		Score += TimeMultiplier * DeltaTime;

		SpawnTimer += DeltaTime;
		if (SpawnTimer >= 1 / SpawnRate)
		{
			SpawnActor();
			SpawnTimer = 0.0f;
		}
	}
	FVector speed(-Speed * DeltaTime, 0, 0);
	int Length = MovingObjects.Num();
	for (int i = Length - 1; i >= 0; i--)
	{
		AActor* actor = MovingObjects[i];
		FVector aPos = actor->GetActorLocation();
		if (aPos.X < -TravelDistance)
		{
			RemoveActor(actor);
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
void ASpawner::ReportAlive()
{
	ActivePlayers++;
}
void ASpawner::ReportHit(AActor* actor)
{
	//Do something cool where the actor was
	RemoveActor(actor);
}
void ASpawner::ReportDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("HaHa, You died!"));
	ActivePlayers--;
	if (ActivePlayers == 0)
	{
		GameActive = false;
		GameEnd();
	}
}

void ASpawner::GameEnd_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Doing some work here"));
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
float ASpawner::GetScore()
{
	return Score;
}
void ASpawner::ReportNearMiss()
{
	UE_LOG(LogTemp, Log, TEXT("Near Miss! %f Points!"), NearMissScore);
	Score += NearMissScore;

	int Length = MovingObjects.Num();
	if (Length == 0) return;

	int rand = FMath::RandRange(Length - 2, Length - 1);
	if (rand < 0) rand = 0;
	if (rand >= Length) rand = Length - 1;

	RemoveActor(MovingObjects[rand]);

}
void ASpawner::SpawnActor()
{
	int rand = FMath::RandRange(LastPosition - 1, LastPosition + 1);
	if (rand < -GridSlots) rand = -GridSlots;
	else if (rand > GridSlots) rand = GridSlots;
	AActor* actor;
	int Length = IdleObjects.Num();
	if (Length > 0)
	{
		actor = IdleObjects[0];
		actor->SetActorLocation(GetActorLocation() + FVector(SpawnDistance, rand * GridDistance, SpawnHeight));
		IdleObjects.Remove(actor);
	}
	else
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, GetActorLocation() + FVector(SpawnDistance, rand * GridDistance, SpawnHeight), GetActorRotation(), SpawnParams);
	}
	MovingObjects.Add(actor);
}
void ASpawner::RemoveActor(AActor* actor)
{
	if (MovingObjects.Find(actor) != -1)
	{
		MovingObjects.Remove(actor);
		actor->SetActorLocation(FVector(SpawnDistance, 0, SpawnHeight));
		IdleObjects.Add(actor);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Trying to remove actor that does not exist!"));
}


