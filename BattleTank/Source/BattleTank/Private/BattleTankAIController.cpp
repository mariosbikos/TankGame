// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"
#include "Tank.h"

class ATank* ABattleTankAIController::GetControlledTank() const
{
	ATank* TankPawn = Cast<ATank>(GetPawn());
	return TankPawn;
}

void ABattleTankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* TankPawn = GetControlledTank();
	if (TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesses: %s"), *TankPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: AIController not possessing a Tank!"));
	}

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank found: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: Couldn't find player tank"));
	}


}

void ABattleTankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}


	
}

ATank* ABattleTankAIController::GetPlayerTank() const
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		return Cast<ATank>(PlayerController->GetPawn());
	}

	UE_LOG(LogTemp, Error, TEXT("Error:Could not find playerController tank"));
	return nullptr;
}
