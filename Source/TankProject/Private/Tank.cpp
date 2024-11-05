// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), GetActorLocation() + FVector(0.f, 0.f, 200.f), 100.f, 12, FColor::Green, true, 10.f);

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;

	if (PlayerControllerRef)
	{
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);	 

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Green, false, -1.f);
	}
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