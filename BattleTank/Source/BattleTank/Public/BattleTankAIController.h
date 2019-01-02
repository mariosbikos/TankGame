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

	class ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	ATank* GetPlayerTank() const;


	
};
