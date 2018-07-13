// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));

	RootComponent = (USceneComponent*)GetCapsuleComponent();

	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->bEditableWhenInherited;
	SpringArm->TargetArmLength = 200;
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;

	OurCamera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);
	OurCamera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	OurCamera->bUsePawnControlRotation = false;

	StateManager = CreateDefaultSubobject<UStateManager>(TEXT("StateManager"));
	StateManager->SetCharacter(this);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -87.0f), FRotator(0.0f, -90.0f, 0.0f));

	bIsProned = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	StateManager->Stand();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMovingX || bMovingY)
	{
		StateManager->Move();
	}
	else
	{
		StateManager->StopMove();
	}

	if (!bWasJumping)
	{
		StateManager->StopJump();
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveX", this, &AMyCharacter::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyCharacter::Move_YAxis);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMyCharacter::TouchStart);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMyCharacter::TouchEnd);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &AMyCharacter::Touching);

	PlayerInputComponent->BindAction("Sight", IE_Pressed, this, &AMyCharacter::GunADS);
	PlayerInputComponent->BindAction("PressX", IE_Pressed, this, &AMyCharacter::PressX);
	PlayerInputComponent->BindAction("PressC", IE_Pressed, this, &AMyCharacter::PressC);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::JumpStart);
}

void AMyCharacter::Move_XAxis(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		bMovingX = true;
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
	else
	{
		bMovingX = false;
	}
}

void AMyCharacter::Move_YAxis(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		bMovingY = true;
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		// add movement in that direction
		AddMovementInput(Direction, value);
	}
	else
	{
		bMovingY = false;
	}
}

void AMyCharacter::Touching(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (!bTouchStart)
	{
		AddControllerYawInput((Location.X - TouchPoint.X) * 0.3);
		SpringArm->AddRelativeRotation(FRotator(-(Location.Y - TouchPoint.Y) * 0.3, 0.0f, 0.0f));
	}
	else {
		bTouchStart = false;
	}
	TouchPoint = Location;
}

void AMyCharacter::TouchStart(ETouchIndex::Type FingerIndex, FVector Location)
{
	bTouchStart = true;
}

void AMyCharacter::TouchEnd(ETouchIndex::Type FingerIndex, FVector Location)
{
	bTouchStart = false;
}

void AMyCharacter::GunADS()
{
	StateManager->GunADS();
}

void AMyCharacter::PressC()
{
	if (bIsCrouched)
	{
		StateManager->StopCrouch();
	}
	else
	{	
		StateManager->Crouch();
	}
}

void AMyCharacter::JumpStart()
{
	StateManager->Jump();
}

void AMyCharacter::PressX()
{
	if (StateManager->IsProne())
	{
		StateManager->StopProne();
	}
	else
	{
		StateManager->Prone();
	}
}

void AMyCharacter::Prone() 
{
	bIsProned = true;
}

void AMyCharacter::UnProne()
{
	bIsProned = false;
}