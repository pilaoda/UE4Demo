// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "JumpState.generated.h"

/**
 * 
 */
UCLASS()
class QUICISTART_API UJumpState : public UBaseState
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UJumpState();
	
	virtual void Enter() override;
	virtual void Leave() override;
	
};
