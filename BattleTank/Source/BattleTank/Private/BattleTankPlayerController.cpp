// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankPlayerController.h"
#include "Tank.h"

ATank* ABattleTankPlayerController::GetControlledTank() const
{
	ATank* TankPawn = Cast<ATank>(GetPawn());
	return TankPawn;
}
