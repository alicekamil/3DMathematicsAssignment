// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "PlayerEntity.generated.h"

UCLASS()
class MATHASSIGNMENT_API APlayerEntity : public AEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerEntity();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 Context;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Players;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;
	
};
