// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerHUD.h"
#include "Spawner.h"

void ARunnerHUD::BeginPlay()
{
	Spawner = ASpawner::GetInstance();
}
void ARunnerHUD::DrawHUD()
{
	float score = Spawner->GetScore();
	FString text = FString::Printf(TEXT("%.0f"), score);
	DrawText(text, Color, screenX, screenY);
}