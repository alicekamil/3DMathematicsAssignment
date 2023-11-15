
#pragma once

#include "CoreMinimal.h"
#include "HeroCharacter.h"
#include "Ability.h"
#include "AbilityTypes.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MATHASSIGNMENT_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AAbility*> Abilities;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AAbility>> AbilityTypes;

public:
	UAbilityComponent();

	TObjectPtr<AHeroCharacter> Player; //?

	UPROPERTY(VisibleAnywhere)
	EAbilityTypes SelectedAbilityType;

	bool IsAnyAbilityBeingUsed();
	bool GetCanUseAbility();
	void StartAbility();
	void SpawnAbility();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

};
