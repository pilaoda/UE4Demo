// Fill out your copyright notice in the Description page of Project Settings.

#include "ProneState.h"
#include "MyCharacter.h"

UProneState::UProneState()
{
	StateName = FString("Prone");
	StateType = StateEnum::PRONE;
}
