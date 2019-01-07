// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"
class UTankBarrel;
class UTankTurret;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	// Sets default values for this pawn's properties
	ATank();

	//This is the standard launch speed of the tank
	UPROPERTY(EditDefaultsOnly,Category=Firing)
	float LaunchSpeed = 4000; //TODO: Find sensible default

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr; //TODO: Remove
public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();
};
