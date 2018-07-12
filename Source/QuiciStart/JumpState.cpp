// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpState.h"
#include "MyCharacter.h"

UJumpState::UJumpState()
{
	StateName = FString("Jump");
	StateType = StateEnum::JUMP;
}

void UJumpState::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Enter"), *StateName);
	Character->Jump();
}

void UJumpState::Leave()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Leave"), *StateName);
}
