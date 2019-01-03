// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//move barrel the right amount this frame

	//given a max elevation speed + frame time
	//given a max elevation speed + frame time

	//Relative speed is from +1 to -1(relative)
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0, 1.0);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSeconds * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange; //current elevation + change
	float NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(NewElevation,0,0));
}
