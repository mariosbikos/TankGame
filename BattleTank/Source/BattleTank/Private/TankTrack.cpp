// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);

	
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0; //reset throttle so that if we are in the air in the next frame, no extra force will be added
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,1);
}

void UTankTrack::DriveTrack()
{
	//TODO: Clamp actual throttle value to disable player from over-drive
	FVector ForceApplied = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation(); //the position on which we apply the force

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
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

