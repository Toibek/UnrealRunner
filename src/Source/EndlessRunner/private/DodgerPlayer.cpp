// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgerPlayer.h"


// Called to bind functionality to input
void ADodgerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveRL"), this, &ADodgerPlayer::Move);
}
void ADodgerPlayer::Move(float Value)
{

	if (!Moved && Value != 0)
	{
		Moved = true;
		ADodger::MoveRL(Value);
	}
	else if (Value == 0)
		Moved = false;
}
