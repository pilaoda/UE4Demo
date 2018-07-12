// Fill out your copyright notice in the Description page of Project Settings.

#include "MoveState.h"
#include "MyCharacter.h"

UMoveState::UMoveState()
{
	StateName = FString("Move");
	StateType = StateEnum::MOVE;
}
