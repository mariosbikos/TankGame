// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"
#include "Tank.h"

void ABattleTankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABattleTankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController) { return; }
	
	ATank* PlayerTank = Cast<ATank>(PlayerController->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	
	if (!PlayerTank || !ControlledTank)
	{
		return;
	}
	
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready
	ControlledTank->Fire();
	


	
}
