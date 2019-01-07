// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTankAIController : public AAIController
{
	GENERATED_BODY()
private:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	//How close the AI tank can get to the player
	float AcceptanceRadius = 3000;
};
