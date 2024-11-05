// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterPawn.h"

// Sets default values
AMasterPawn::AMasterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(CapsuleComponent);

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	CannonMesh->SetupAttachment(BodyMesh);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn->SetupAttachment(CannonMesh);
}

// Called when the game starts or when spawned
void AMasterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMasterPawn::RotateTurret(FVector LookAtTarget) 
{
	FVector ToTarget = LookAtTarget - CannonMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	CannonMesh->SetWorldRotation(LookAtRotation);
}

// Called every frame
void AMasterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMasterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

