// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	
	GetChildrenComponents(false)
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//TODO: Clamp actual throttle value to disable player from over-drive
	float ForceApplied = CurrentThrottle*TrackMaxDrivingForce;

	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

void UTankTrack::ApplySidewaysForce()
{
	//Calculate slippage speed(component of speed in the tank right direction). 0 if no slippage. If sliding entirely sideways then it should be speed.
	//So it is the cos of the angle between velocity of tank and the sideways(right) vector
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//work out required acceleration this frame to correct(a) 
	//So if we are moving sideways at 10cm /s, then this frame in this delta time we need a certain amount of acceleration to fix that velocity down to 0.
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();

	//calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()));
	auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;// 2 tracks

	TankRoot->AddForce(CorrectionForce);
}

