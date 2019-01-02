// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTankPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	class ATank* GetControlledTank() const;
};
