// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Entity.generated.h"

UCLASS(hidecategories=(Collision, Rendering, HLOD, WorldPartition, DataLayers, Replication, Physics, Networking, Actor, LevelInstance, Cooking))
class MATHASSIGNMENT_API AEntity : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEntity();

protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;
	
};
