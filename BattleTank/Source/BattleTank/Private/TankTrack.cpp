// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s has Throttle: %f"), *GetOwner()->GetName(),Throttle);

	//TODO: Clamp actual throttle value to disable player from over-drive
}
