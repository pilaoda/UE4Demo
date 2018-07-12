// Fill out your copyright notice in the Description page of Project Settings.

#include "ProneState.h"
#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"

UProneState::UProneState()
{
	StateName = FString("Prone");
	StateType = StateEnum::PRONE;
}

void UProneState::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Enter"), *StateName);
	Character->Prone();

	Character->GetCapsuleComponent()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void UProneState::Leave()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Leave"), *StateName);
	Character->UnProne();
}
