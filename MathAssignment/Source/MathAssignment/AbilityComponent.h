
#pragma once

#include "CoreMinimal.h"
#include "HeroCharacter.h"
#include "Ability.h"
#include "IntersectionSubSystem.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MATHASSIGNMENT_API UAbilityComponent : public UActorComponent, public ISpawnVFX
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AAbility*> Abilities;

	UPROPERTY()
	AAbility* currAbility;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AAbility>> AbilityTypes;

public:
	UAbilityComponent();

	TObjectPtr<AHeroCharacter> Player; //?
	
	TArray<int32> abilityContexts;
	void GetAbilityContexts(TArray<AAbility*> ContextAbilities);
	
	UFUNCTION(BlueprintCallable)
	void PlayVFX();
	UPROPERTY()
	UIntersectionSubsystem* SubSystem;
	

	bool IsAnyAbilityBeingUsed();
	bool GetCanUseAbility();
	void StartAbility(int index);
	
	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

	

};
