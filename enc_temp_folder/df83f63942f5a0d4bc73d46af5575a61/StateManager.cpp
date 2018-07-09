// Fill out your copyright notice in the Description page of Project Settings.

#include "StateManager.h"
#include "StandState.h"
#include "CrouchState.h"
#include "CreepState.h"
#include "MoveState.h"
#include "HaltState.h"
#include "OpenState.h"
#include "CloseState.h"

// Sets default values for this component's properties
UStateManager::UStateManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UStateManager::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UStateManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UE_LOG(LogTemp, Warning, TEXT("Current State: { H1:%s, H2:%s, H3:%s }"), *H1_State->StateName, *H2_State->StateName, *H3_State->StateName);
}

UBaseState* UStateManager::GetStateObject(FString StateName)
{
	if (StateName == "stand_state")
	{
		return NewObject<UStandState>();
	}
	else if (StateName == "crouch_state")
	{
		return NewObject<UCrouchState>();
	}
	else if (StateName == "creep_state")
	{
		return NewObject<UCreepState>();
	}
	else if (StateName == "move_state")
	{
		return NewObject<UMoveState>();
	}
	else if (StateName == "halt_state")
	{
		return NewObject<UHaltState>();
	}
	else if (StateName == "open_state")
	{
		return NewObject<UOpenState>();
	}
	else if (StateName == "close_state")
	{
		return NewObject<UCloseState>();
	}
	else
	{
		check(false);
		return false;
	}

}

void UStateManager::Stand() {
	FString StateName = "stand_state";
	H1_State = GetStateObject(StateName);
}


void UStateManager::Crouch() {
	FString StateName = "crouch_state";
	H1_State = GetStateObject(StateName);
}


void UStateManager::Creep() {
	FString StateName = "creep_state";
	H1_State = GetStateObject(StateName);
}


void UStateManager::Move() {
	FString StateName = "move_state";
	H2_State = GetStateObject(StateName);
}


void UStateManager::Halt() {
	FString StateName = "halt_state";
	H2_State = GetStateObject(StateName);
}


void UStateManager::Open() {
	FString StateName = "open_state";
	H3_State = GetStateObject(StateName);
}


void UStateManager::Close() {
	FString StateName = "close_state";
	H3_State = GetStateObject(StateName);
}