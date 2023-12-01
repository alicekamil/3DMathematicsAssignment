#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Particles/ParticleSystem.h"
#include "MeleeAbility.generated.h"


class UAnimMontage;

USTRUCT(BlueprintType)
struct FMeleeAbilityProperties
{
	GENERATED_BODY()

	FName AbilityName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	UFXSystemAsset* SlashVFX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability")
	UFXSystemAsset* ImpactVFX;
	UPROPERTY(EditDefaultsOnly, Category="Montages")
	UAnimMontage* AbilityAnimMontage;
	
	float HurtBoxRange;
	float HurtBoxWidth;
	float HurtBoxHeight;
	float HurtBoxLifeTime;
	float DamageIntensity;
};

UCLASS()
class MATHASSIGNMENT_API AMeleeAbility : public AAbility
{
	GENERATED_BODY()

public:
	AMeleeAbility();

protected:

	FMeleeAbilityProperties properties;
	
	virtual void BeginPlay() override;

	virtual void CastAbility() override;

public:
	virtual void Tick(float DeltaTime) override;
};
