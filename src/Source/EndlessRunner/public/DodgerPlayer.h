// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dodger.h"
#include "DodgerPlayer.generated.h"

/**
 *
 */
UCLASS()
class ENDLESSRUNNER_API ADodgerPlayer : public ADodger
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(float Value);
private:
	bool Moved = false;
};
