// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "GunReloadState.generated.h"

/**
 * 
 */
UCLASS()
class QUICISTART_API UGunReloadState : public UBaseState
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UGunReloadState();
	
	virtual void Enter() override;
	virtual void Leave() override;

	bool bFinish;
};
