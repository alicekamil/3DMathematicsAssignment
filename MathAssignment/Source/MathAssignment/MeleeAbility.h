// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "GameFramework/Actor.h"
#include "MeleeAbility.generated.h"

UCLASS()
class MATHASSIGNMENT_API AMeleeAbility : public AAbility
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMeleeAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnInitVFX(UFXSystemAsset* VFX) override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
