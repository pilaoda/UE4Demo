// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "BaseState.h"
class AMyCharacter;
#include "StateManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUICISTART_API UStateManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateManager();
	UStateManager(AMyCharacter* Character);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddState(StateEnum StateType);
	void RemoveState(StateEnum StateType);
	UBaseState* GetStateObject(StateEnum StateType);
	void SetCharacter(AMyCharacter* Character);

	void Move();
	void StopMove();
	void Stand();
	void Crouch();
	void StopCrouch();
	void Prone();
	void StopProne();
	void Jump();
	void StopJump();
	void GunADS();
	void GunFire();
	void StopGunFire();
	void GunReload();
	void FinishGunReload();
	void StopGunReload();

	void ShowCurrentStates();
	bool IsProne();


	bool HasX(FString s);
	bool HasY(FString s);

	UPROPERTY()
		TSet<UBaseState*> CurrentStates;

	UPROPERTY()
		UBaseState* MoveState;
	UPROPERTY()
		UBaseState* StandState;
	UPROPERTY()
		UBaseState* CrouchState;
	UPROPERTY()
		UBaseState* ProneState;
	UPROPERTY()
		UBaseState* JumpState;
	UPROPERTY()
		UBaseState* GunFireState;
	UPROPERTY()
		UBaseState* GunADSState;
	UPROPERTY()
		UBaseState* GunReloadState;

	// 	MOVE, STAND, CROUCH, PRONE, JUMP, GUN_FIRE, GUN_ADS, GUN_RELOAD
	const FString StateTable[8][8] = {
			{ "XY", "XY", "XY", "XY", "XY", "XY", "XY", "XY" },
			{ "XY", "XY", "_Y", "_Y", "XY", "XY", "XY", "XY" },
			{ "XY", "_Y", "X_", "_Y", "XY", "XY", "XY", "XY" },
			{ "XY", "_Y", "_Y", "XY", "X_", "XY", "XY", "XY" },
			{ "XY", "XY", "X_", "X_", "XY", "XY", "X_", "XY" },
			{ "XY", "XY", "XY", "XY", "XY", "XY", "X_", "_Y" },
			{ "XY", "XY", "XY", "XY", "_Y", "XY", "XY", "_Y" },
			{ "XY", "XY", "XY", "XY", "XY", "_Y", "X_", "X_" }
	};

	TMap<StateEnum, TArray<TMap<FString, FString>>> Conditions;

	FTimerHandle TimeHandel;
};