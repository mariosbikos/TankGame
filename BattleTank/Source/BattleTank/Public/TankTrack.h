// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"
class ASprungWheel;
/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	void DriveTrack(float CurrentThrottle);

	void ApplySidewaysForce();

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Throttle)
	float TrackMaxDrivingForce = 40000000; //Assume 40000Kg tank and 1g accel(10m/s^2). 
	
private:

	UTankTrack();
	
	TArray<ASprungWheel*> GetWheels() const;
};
