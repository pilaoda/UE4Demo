// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Map.h"
#include "BaseState.h"
#include "StandState.h"
#include "StateManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class QUICISTART_API UStateManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UBaseState* GetStateObject(FString StateName);

	void Stand();
	void Crouch();
	void Creep();
	void Move();
	void Halt();
	void Open();
	void Close();

	UPROPERTY()
		UBaseState* H1_State;
	UPROPERTY()
		UBaseState* H2_State;
	UPROPERTY()
		UBaseState* H3_State;

	UPROPERTY()
		UBaseState* H1_Replace_State;
	UPROPERTY()
		UBaseState* H2_Replace_State;
	UPROPERTY()
		UBaseState* H3_Replace_State;

};
