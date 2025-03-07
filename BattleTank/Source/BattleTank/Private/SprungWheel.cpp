// Copyright MythGameFactory Ltd.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass-Wheel Constraint"));
	SetRootComponent(MassWheelConstraint);

	Axle2 = CreateDefaultSubobject<USphereComponent>(FName("Axle2"));
	Axle2->SetupAttachment(MassWheelConstraint);

	Wheel2 = CreateDefaultSubobject<USphereComponent>(FName("Wheel2"));
	Wheel2->SetupAttachment(Axle2);
	

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle-Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle2);


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel2->SetNotifyRigidBodyCollision(true);
	Wheel2->OnComponentHit.AddUniqueDynamic(this,&ASprungWheel::OnHit);
	SetupConstraints();

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}


}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }

	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }

	MassWheelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle2, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle2, NAME_None, Wheel2, NAME_None);
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel2->AddForce(TotalForceMagnitudeThisFrame*Axle2->GetForwardVector());
}

