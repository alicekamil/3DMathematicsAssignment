
#include "MeleeAbility.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMeleeAbility::AMeleeAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

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

