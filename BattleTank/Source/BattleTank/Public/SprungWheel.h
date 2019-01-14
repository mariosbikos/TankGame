// Copyright MythGameFactory Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);
private:
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Wheel2 = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Axle2 = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	class UPhysicsConstraintComponent* MassWheelConstraint = nullptr; //This now is the mass/axle constraint
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	class UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	void SetupConstraints();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;
};
