// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"
#include "TankAimingComponent.h"
//Depends on movement component via pathfinding system

void ABattleTankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ABattleTankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!ensure(PlayerTank) && !ensure(ControlledTank)){return;}
	
	//Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready
	AimingComponent->Fire();

}
