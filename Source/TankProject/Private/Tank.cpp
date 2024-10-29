// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &ATank::Move);
			EnhancedInputComponent->BindAction(InputActionTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
		}
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	FVector Movement = FVector::ZeroVector;
	Movement.X = Value.Get<float>() * TravelSpeed;
	AddActorLocalOffset(Movement);
}

void ATank::Turn(const FInputActionValue& Value)
{
	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = Value.Get<float>() * RotationSpeed * -1.f;
	AddActorLocalRotation(Rotation);
}