// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
public:
	//Returns current health as a percentage of starting health between 0-1
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
	UPROPERTY(BlueprintAssignable,Category = "Health")
	FOnDeathDelegate OnDeath;
private:

	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;
	//called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

};
