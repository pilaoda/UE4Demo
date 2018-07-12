// Fill out your copyright notice in the Description page of Project Settings.

#include "CrouchState.h"
#include "MyCharacter.h"

UCrouchState::UCrouchState()
{
	StateName = FString("Crouch");

	StateType = StateEnum::CROUCH;
}


void UCrouchState::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Enter"), *StateName);
	Character->Crouch();
}

void UCrouchState::Leave()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Leave"), *StateName);
	Character->UnCrouch();
}

