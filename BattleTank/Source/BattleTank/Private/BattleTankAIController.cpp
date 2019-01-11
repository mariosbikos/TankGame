// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

	//Fire if locked only for AI, while player can also fire when at aim state
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
	

}

void ABattleTankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		
		//subscribe local method to tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ABattleTankAIController::OnPossessedTankDeath);
	}
}

void ABattleTankAIController::OnPossessedTankDeath()
{
	auto ControlledTank = GetPawn();
	UE_LOG(LogTemp, Warning, TEXT("Tank: %s is now dead. AI Unpossessing tank"), *GetPawn()->GetName());
	ControlledTank->DetachFromControllerPendingDestroy();
}
