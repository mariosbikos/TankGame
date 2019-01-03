// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Spin(float RelativeSpeed)
{
	//move turret the right amount this frame

	//Relative speed is from +1 to -1(relative)
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float SpinChange = RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	float NewRotation = RelativeRotation.Yaw + SpinChange; //current elevation + change
	//float NewRotation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(0, NewRotation, 0));
}