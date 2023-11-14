// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "CollisionShape.h"
#include "Intersections.h"
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

	virtual void BeginPlay() override;
	
	virtual bool ShouldTickIfViewportsOnly() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EIntersection> IntersectionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sphere")
	float Radius;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V2;

	UPROPERTY()
	bool Drawn;
	
	void DrawShape(const FColor Color);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 Context;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Players;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;
	
};
