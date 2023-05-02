// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dodger.h"
#include "DodgerBot.generated.h"

/**
 *
 */
UCLASS()
class ENDLESSRUNNER_API ADodgerBot : public ADodger
{
	GENERATED_BODY()

public:
	ADodgerBot();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Bot")
		float ThinkTime = 0.2;
	UPROPERTY(EditAnywhere, Category = "Bot")
		float SightDistance = 250;

private:
	void Think();
	float ThinkTimer;
};
