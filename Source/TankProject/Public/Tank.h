// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterPawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TANKPROJECT_API ATank : public AMasterPawn
{
	GENERATED_BODY()
	
public:
	ATank();

private:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* FollowCamera;
};
