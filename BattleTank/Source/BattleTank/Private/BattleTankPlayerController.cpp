// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTankPlayerController.h"
#include "Tank.h"

ATank* ABattleTankPlayerController::GetControlledTank() const
{
	ATank* TankPawn = Cast<ATank>(GetPawn());
	return TankPawn;
}

void ABattleTankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* TankPawn = GetControlledTank();
	if (TankPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesses %s"), *TankPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: PlayerController not possessing a Tank!"));
	}
	


}

void ABattleTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();

		//Find where 2D ui is raycasting on 3D world
		//move the barrel gradually towards that hit world location(up/down only). Do the same for turret(left/right only)
}

void ABattleTankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	FVector HitLocation; //OUT Parameter
	if (GetSightRayHitLocation(HitLocation)) //is going to line-trace
	{
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
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
		if (GetLookVectorHitLocation(OutLookDirection, OutHitLocation))
		{
			return true;
		}

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