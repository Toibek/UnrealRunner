// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "GameFramework/HUD.h"
#include "RunnerHUD.generated.h"

/**
 *
 */
UCLASS()
class ENDLESSRUNNER_API ARunnerHUD : public AHUD
{
	GENERATED_BODY()

private:
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	ASpawner* Spawner;
public:
	UPROPERTY(EditAnywhere, Category = "Score")
		float screenX;
	UPROPERTY(EditAnywhere, Category = "Score")
		float screenY;
	UPROPERTY(EditAnywhere, Category = "Score")
		FLinearColor Color;
	UPROPERTY(EditAnywhere, Category = "Score")
		float Scale;
	UPROPERTY(EditAnywhere, Category = "Score")
		bool bScalePosition;
};
