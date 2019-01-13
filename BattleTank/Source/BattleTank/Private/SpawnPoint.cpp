// Copyright MythGameFactory Ltd.

#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	AActor* ActorSpawned = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass,GetComponentTransform());
	if (!ActorSpawned) { return; }

	ActorSpawned->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	// ...
	UGameplayStatics::FinishSpawningActor(ActorSpawned, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

