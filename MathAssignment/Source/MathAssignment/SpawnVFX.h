// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystem.h"
#include "UObject/Interface.h"
#include "SpawnVFX.generated.h"

/**
 * Must have BlueprintType as a specifier to have this interface exposed to blueprints.
 * With this line you can easily add this interface to any blueprint class.
 */
UINTERFACE(BlueprintType)
class MATHASSIGNMENT_API USpawnVFX : public UInterface
{
	GENERATED_BODY()
};
class MATHASSIGNMENT_API ISpawnVFX
{
	GENERATED_BODY()
	
public:
	// if i wanna impl in blueprint, need to have nativeevent
	virtual void SpawnInitVFX(UFXSystemAsset* VFX);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BPSpawnVFX(UFXSystemAsset* VFX);
};

