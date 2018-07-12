// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseState.h"
#include "MyCharacter.h"

// Sets default values for this component's properties
UBaseState::UBaseState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// 	PrimaryComponentTick.bCanEverTick = true;

	StateName = FString("base");
	StateType = (StateEnum)-1;
}


// Called when the game starts
void UBaseState::BeginPlay()
{
	Super::BeginPlay();

// 	UE_LOG(LogTemp, Warning, TEXT("%s begin play"), *StateName);
}


// Called every frame
void UBaseState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

// 	UE_LOG(LogTemp, Warning, TEXT("%s tick"), *StateName);
}

void UBaseState::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Enter"), *StateName);
}

void UBaseState::Leave()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Leave"), *StateName);
}

void UBaseState::SetCharacter(AMyCharacter* Character)
{
	this->Character = Character;
}