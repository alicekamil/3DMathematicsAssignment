
#include "MeleeAbility.h"


// Sets default values
AMeleeAbility::AMeleeAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeleeAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeleeAbility::SpawnInitVFX(UFXSystemAsset* VFX)
{
	Super::SpawnInitVFX(VFX);
	
}

// Called every frame
void AMeleeAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

