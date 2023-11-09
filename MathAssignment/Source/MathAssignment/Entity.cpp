#include "Entity.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

