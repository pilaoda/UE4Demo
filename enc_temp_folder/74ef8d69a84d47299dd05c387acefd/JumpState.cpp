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
	Character->Jump();
}

void UJumpState::Leave()
{
}
