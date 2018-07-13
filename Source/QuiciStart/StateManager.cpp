// Fill out your copyright notice in the Description page of Project Settings.

#include "StateManager.h"
#include "MoveState.h"
#include "StandState.h"
#include "CrouchState.h"
#include "ProneState.h"
#include "JumpState.h"
#include "GunFireState.h"
#include "GunADSState.h"
#include "GunReloadState.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

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
	GunReloadState = NewObject<UGunReloadState>();

	TArray<TMap<FString, FString>> ProneArray;

	TMap<FString, FString> m1;
	m1.Add("from", FString::FromInt((int)StateEnum::MOVE));
	m1.Add("to", FString::FromInt((int)StateEnum::GUN_ADS));
	m1.Add("relation", "_Y");
	ProneArray.Add(m1);

	TMap<FString, FString> m2;
	m2.Add("from", FString::FromInt((int)StateEnum::GUN_ADS));
	m2.Add("to", FString::FromInt((int)StateEnum::MOVE));
	m2.Add("relation", "_Y");
	ProneArray.Add(m2);

	Conditions.Add(StateEnum::PRONE, ProneArray);
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
		ShowCurrentStates();
	}

	if (CurrentStates.Find(GetStateObject(AddStateType)))
	{
		return;
	}

	// check conditions
	for (auto& Elem : Conditions)
	{
		if (CurrentStates.Find(GetStateObject(Elem.Key)))
		{
			TArray<TMap<FString, FString>> array = Elem.Value;
			for (auto& r : array) {
				StateEnum from = (StateEnum)FCString::Atoi(*r["from"]);
				StateEnum to = (StateEnum)FCString::Atoi(*r["to"]);
				FString s = r["relation"];
				if (CurrentStates.Find(GetStateObject(from)))
				{
					if (AddStateType == to)
					{
						if (!HasX(s))
						{
							RemoveState(from);
						}
						if (HasY(s))
						{
							UBaseState* state = GetStateObject(to);
							CurrentStates.Add(state);
							state->Enter();
						}
						ShowCurrentStates();
						return;
					}
				}
			}
		}
	}


	TArray<StateEnum> ToBeRemoved;
	bool NeedAdd = false;
	for (auto& State : CurrentStates)
	{
		FString s = StateTable[(int)State->StateType][(int)AddStateType];
		if (!HasX(s))
		{
			ToBeRemoved.Add(State->StateType);
		}
		if (HasY(s))
		{
			NeedAdd = true;
		}
	}
	for (auto& StateType : ToBeRemoved)
	{
		RemoveState(StateType);
	}
	if (NeedAdd)
	{
		UBaseState* state = GetStateObject(AddStateType);
		CurrentStates.Add(state);
		state->Enter();
	}
	ShowCurrentStates();

}

void UStateManager::RemoveState(StateEnum StateType)
{
	UBaseState* state = GetStateObject(StateType);
	if (CurrentStates.Find(state))
	{
		CurrentStates.Remove(state);
		state->Leave();
		ShowCurrentStates();
	}
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
	else if (StateType == StateEnum::GUN_RELOAD)
	{
		return GunReloadState;
	}
	else
	{
		check(false);
		return false;
	}

}

void UStateManager::SetCharacter(AMyCharacter * Character)
{
	MoveState->SetCharacter(Character);
	StandState->SetCharacter(Character);
	CrouchState->SetCharacter(Character);
	ProneState->SetCharacter(Character);
	JumpState->SetCharacter(Character);
	GunFireState->SetCharacter(Character);
	GunADSState->SetCharacter(Character);
}

void UStateManager::Move() {
	AddState(StateEnum::MOVE);
}

void UStateManager::StopMove() {
	RemoveState(StateEnum::MOVE);
}

void UStateManager::Stand() {
	AddState(StateEnum::STAND);
}

void UStateManager::Crouch() {
	AddState(StateEnum::CROUCH);
}

void UStateManager::StopCrouch() {
	RemoveState(StateEnum::CROUCH);
}

void UStateManager::Prone() {
	AddState(StateEnum::PRONE);
}

void UStateManager::StopProne() {
	RemoveState(StateEnum::PRONE);
}

void UStateManager::Jump() {
	AddState(StateEnum::JUMP);
}

void UStateManager::StopJump() {
	RemoveState(StateEnum::JUMP);
}

void UStateManager::GunADS() {
	UBaseState** PState = CurrentStates.Find(GunADSState);
	if (PState != nullptr)
	{
		RemoveState(StateEnum::GUN_ADS);
	}
	else
	{
		AddState(StateEnum::GUN_ADS);
	}
}

void UStateManager::GunFire() {
	AddState(StateEnum::GUN_FIRE);
}

void UStateManager::StopGunFire() {
	RemoveState(StateEnum::GUN_FIRE);
}

void UStateManager::ShowCurrentStates() {
	FString msg = "";
	for (auto& State : CurrentStates)
	{
		msg += State->StateName + " ";
	}
	UE_LOG(LogTemp, Warning, TEXT("Current States: %s"), *msg);
}

bool UStateManager::IsProne()
{
	return CurrentStates.Contains(ProneState);
}

void UStateManager::GunReload()
{
	AddState(StateEnum::GUN_RELOAD);
	FTimerHandle TimeHandel;
	GetWorld()->GetTimerManager().SetTimer(TimeHandel, this, &UStateManager::FinishGunReload, 1.0f, true);
	GetWorld()->GetTimerManager().ClearTimer(TimeHandel);
}

void UStateManager::FinishGunReload()
{
	if (CurrentStates.Contains(GunReloadState))
	{
		((UGunReloadState *)GunReloadState)->bFinish = true;
		RemoveState(StateEnum::GUN_RELOAD);
	}
}

void UStateManager::StopGunReload()
{
	RemoveState(StateEnum::GUN_RELOAD);
}