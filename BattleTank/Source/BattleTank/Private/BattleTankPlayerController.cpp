// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"



void ABattleTankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) return;
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
	
}

void ABattleTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();

}

void ABattleTankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; //OUT Parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	
	if (bGotHitLocation) //is going to line-trace
	{
		//Tell controlled tank to aim at this point
		AimingComponent->AimAt(HitLocation);
	}

}

bool ABattleTankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//find cross-hair position
	int32 ViewportSizeX, ViewportSizeY; //size of current viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//Now get where the UI target dot is on the current viewport.
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//De-project screen position of cross-hair to a world direction
	FVector OutLookDirection;
	if(GetLookDirection(ScreenLocation, OutLookDirection))
	{
		//Line-trace along that look direction and see what we hit up to a max-range
		return GetLookVectorHitLocation(OutLookDirection, OutHitLocation);

	}
	return false;
}

bool ABattleTankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const 
{
	//De-project screen position of cross-hair to a world direction
	FVector OutCameraWorldLocation, OutWorldDirection;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		OutCameraWorldLocation, 
		OutLookDirection);
}

bool ABattleTankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutLookVectorHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LineTraceRange * LookDirection;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation, 
			EndLocation, 
			ECollisionChannel::ECC_Camera
		))
	{
		OutLookVectorHitLocation = HitResult.Location;
		return true;
	}

	OutLookVectorHitLocation = FVector(0);
	return false;
}


void ABattleTankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PlayerTank = Cast<ATank>(InPawn);
		if (!ensure(PlayerTank)) { return; }

		//subscribe local method to tank's death event
		PlayerTank->OnDeath.AddUniqueDynamic(this, &ABattleTankPlayerController::OnPossessedTankDeath);
	}
}


void ABattleTankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}
