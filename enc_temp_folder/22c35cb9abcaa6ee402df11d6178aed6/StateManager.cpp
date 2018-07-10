// Fill out your copyright notice in the Description page of Project Settings.

#include "StateManager.h"
#include "MoveState.h"
#include "StandState.h"
#include "CrouchState.h"
#include "ProneState.h"
#include "JumpState.h"
#include "GunFireState.h"
#include "GunADSState.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UStateManager::UStateManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FString json = "";
	FString filePath = "States.json";
	FString gameDir = FPaths::ProjectDir();

	FFileHelper::LoadFileToString(json, *(gameDir + filePath));

	UE_LOG(LogTemp, Warning, TEXT("json %s %s"), *gameDir, *json);

	MoveState = NewObject<UMoveState>();
	StandState = NewObject<UStandState>();
	CrouchState = NewObject<UCrouchState>();
	ProneState = NewObject<UProneState>();
	JumpState = NewObject<UJumpState>();
	GunFireState = NewObject<UGunFireState>();
	GunADSState = NewObject<UGunADSState>();

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

}

bool UStateManager::HasX(FString s)
{
	if (s[0] == 'X')
	{
		return true;
	}
	return false;
}

bool UStateManager::HasY(FString s)
{
	if (s[1] == 'Y')
	{
		return true;
	}
	return false;
}

void UStateManager::AddState(StateEnum AddStateType)
{
	if (CurrentStates.Num() == 0)
	{
		UBaseState* state = GetStateObject(AddStateType);
		CurrentStates.Add(state);
		state->Enter();
	}
	else
	{
		TArray<StateEnum> ToBeRemoved;
		for (auto& State : CurrentStates)
		{
			FString s = StateTable[(int)State->StateType][(int)AddStateType];
			if (!HasX(s))
			{
				ToBeRemoved.Add(State->StateType);
			}
			if (HasY(s))
			{
				UBaseState* state = GetStateObject(AddStateType);
				CurrentStates.Add(state);
				state->Enter();
			}
		}
		for (auto& StateType : ToBeRemoved)
		{
			RemoveState(StateType);
		}
	}
}

void UStateManager::RemoveState(StateEnum StateType)
{
	UBaseState* state = GetStateObject(StateType);
	CurrentStates.Remove(state);
	state->Leave();
}

UBaseState* UStateManager::GetStateObject(StateEnum StateType)
{
	if (StateType == StateEnum::MOVE)
	{
		return MoveState;
	}
	else if (StateType == StateEnum::STAND)
	{
		return StandState;
	}
	else if (StateType == StateEnum::CROUCH)
	{
		return CrouchState;
	}
	else if (StateType == StateEnum::PRONE)
	{
		return ProneState;
	}
	else if (StateType == StateEnum::JUMP)
	{
		return JumpState;
	}
	else if (StateType == StateEnum::GUN_FIRE)
	{
		return GunFireState;
	}
	else if (StateType == StateEnum::GUN_ADS)
	{
		return GunADSState;
	}
	else
	{
		check(false);
		return false;
	}

}


void UStateManager::Move() {
	AddState(StateEnum::MOVE);
}

void UStateManager::Stand() {
	AddState(StateEnum::STAND);
}

void UStateManager::Crouch() {
	UBaseState** PState = CurrentStates.Find(CrouchState);
	if (PState != nullptr)
	{
		RemoveState(StateEnum::CROUCH);
		AddState(StateEnum::STAND);
	}
	else
	{
		AddState(StateEnum::CROUCH);
	}
}

void UStateManager::Prone() {
	UBaseState** PState = CurrentStates.Find(ProneState);
	if (PState != nullptr)
	{
		RemoveState(StateEnum::PRONE);
		AddState(StateEnum::STAND);
	}
	else
	{
		AddState(StateEnum::PRONE);
	}
}

void UStateManager::Jump() {
	AddState(StateEnum::JUMP);
}

void UStateManager::GunADS() {
	AddState(StateEnum::GUN_ADS);
}

void UStateManager::GunFire() {
	AddState(StateEnum::GUN_FIRE);
}
