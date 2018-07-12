// Fill out your copyright notice in the Description page of Project Settings.

#include "StandState.h"
#include "MyCharacter.h"

UStandState::UStandState()
{
	StateName = FString("Stand");

	StateType = StateEnum::STAND;
}
