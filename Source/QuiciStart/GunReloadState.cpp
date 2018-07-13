// Fill out your copyright notice in the Description page of Project Settings.

#include "GunReloadState.h"
#include "MyCharacter.h"

UGunReloadState::UGunReloadState()
{
	StateName = FString("GunReload");
	StateType = StateEnum::GUN_RELOAD;
	bFinish = false;
}

void UGunReloadState::Enter()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Enter"), *StateName);
	Character->GunReload();
}

void UGunReloadState::Leave()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Leave"), *StateName);
	if (bFinish)
	{
		Character->FinishGunReload();
		bFinish = false;
	}
	else
	{
		Character->StopGunReload();
	}
}
