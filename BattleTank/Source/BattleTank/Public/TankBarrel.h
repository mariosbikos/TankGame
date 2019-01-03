// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
//Holds barrel's properties and Elevate Method
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 is max downward speed and +1 is max up movement(from -1 to +1)
	void Elevate(float RelativeSpeed);

	UPROPERTY(EditAnywhere,Category = Setup)
	float MaxDegreesPerSeconds = 20; //speed of barrel moving around
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;
};
