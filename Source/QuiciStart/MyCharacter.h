// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "StateManager.h"

#include "MyCharacter.generated.h"

UCLASS()
class QUICISTART_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Move_XAxis(float value);
	void Move_YAxis(float value);
	void TouchStart(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchEnd(ETouchIndex::Type FingerIndex, FVector Location);
	void Touching(ETouchIndex::Type FingerIndex, FVector Location);
	void GunADS();
	void PressX();
	void PressC();

	bool bTouchStart;
	bool bMovingX;
	bool bMovingY;
	FVector TouchPoint;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
		UCameraComponent* OurCamera;

	UStateManager* StateManager;

};
