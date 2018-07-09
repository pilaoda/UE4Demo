// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
// 
// 	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
// 	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
// 
// 	OurCamera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
// 	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
// 	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
// 	OurVisibleComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		float x = GetActorForwardVector().X;
		float y = GetActorForwardVector().Y;
		float angle = FMath::Acos(y);
		float angle2 = -FMath::Asin(x);

		if (angle2 > 0)
		{
			angle = -angle;
		};

		FVector RelativeVecForward = CurrentVelocity.GetUnsafeNormal();
		RelativeVecForward.Normalize();

		float sina = FMath::Sin(angle);
		float cosa = FMath::Cos(angle);
		float tx = CurrentVelocity.X * cosa + CurrentVelocity.Y * sina;
		float ty = -CurrentVelocity.X * sina + CurrentVelocity.Y * cosa;
		FVector moved = FVector(tx, ty, 0.0f) * DeltaTime;

		FVector NewLocation = GetActorLocation() + moved;
		SetActorRelativeLocation(NewLocation);
	}

	if (!CurrentAngular.IsZero())
	{
		FRotator NewForward = GetActorRotation() + (CurrentAngular * DeltaTime);
		NewForward.Pitch = GetActorRotation().Pitch;
		SetActorRotation(NewForward);

		FRotator NewCameraForward = OurCamera->GetComponentRotation() + (CurrentAngular * DeltaTime);
		OurCamera->SetRelativeRotation(FRotator(NewCameraForward.Pitch, 0.0f, 0.0f));
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

// 	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
// 	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
// 
// 	InputComponent->BindAxis("RotateYaw", this, &AMyPawn::Rotate_Yaw);
// 	InputComponent->BindAxis("RotatePitch", this, &AMyPawn::Rotate_Pitch);
}

void AMyPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}
// 
// void AMyPawn::Rotate(float AxisValue)
// {
// 	CurrentAngular.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
// }
