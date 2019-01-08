// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AProjectile> ProjectileClassAsset(TEXT("/Game/Tank/BP_Projectile"));
	if (ProjectileClassAsset.Succeeded())
	{
		ProjectileClass = ProjectileClassAsset.Class;
	}
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the outLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal(); //Get the unit direction of a vector
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s with Launch Speed: %f"), *GetOwner()->GetName(), *HitLocation.ToString(), *Barrel->GetComponentLocation().ToString(), LaunchSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s -> Aim solution found"), *GetOwner()->GetName());
		//Move the barrel
		MoveBarrelTowards(AimDirection); 
		MoveTurretTowards(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank: %s -> No Aim Solve Found"),*GetOwner()->GetName());
	}
}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	if (!Barrel) { return; }
	//Work out difference between current barrel rotation and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); //Pitch will be clamped from (-1,1) in Elevate method. 

	
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{

	if (!Turret) { return; }
	//Work out difference between current turret rotation and aim direction
	FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	if (DeltaRotator.Yaw<180.0f && DeltaRotator.Yaw>-180.0f)
	{
		Turret->Rotate(DeltaRotator.Yaw); //Pitch will be clamped from (-1,1) in Elevate method.
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw); //Pitch will be clamped from (-1,1) in Elevate method.
	}
	
}

void UTankAimingComponent::Fire()
{


	if (FiringState!=EFiringStatus::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		// Spawn a projectile at the socket location on the barrel

		if (!ensure(ProjectileClass)) { return; }

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileClass,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	return !(AimDirection.Equals(Barrel->GetForwardVector(),0.01));
}

