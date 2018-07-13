// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.generated.h"
class AMyCharacter;

UENUM(BlueprintType)
enum class StateEnum : uint8
{
	MOVE = 0,
	STAND = 1,
	CROUCH = 2,
	PRONE = 3,
	JUMP = 4,
	GUN_FIRE = 5,
	GUN_ADS = 6,
	GUN_RELOAD = 7
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUICISTART_API UBaseState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Enter();
	virtual void Leave();

	virtual void SetCharacter(AMyCharacter * Character);

		
	FString StateName;
	StateEnum StateType;
	AMyCharacter* Character;
};