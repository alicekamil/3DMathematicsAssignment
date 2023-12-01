
#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "InstantAbility.generated.h"

UCLASS()
class MATHASSIGNMENT_API AInstantAbility : public AAbility
{
	GENERATED_BODY()

public:
	AInstantAbility();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void CastAbility() override;
};
