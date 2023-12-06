
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroCharacter.h"
#include "ContextHelpers.h"
#include "Ability.generated.h"

class UAnimInstance;
class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityDestroyed);

UCLASS()
class MATHASSIGNMENT_API AAbility : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbility();
	//CanbeUsed - called from Ability component - abstract
	//OnStartUsed - called from Ability component - abstract
	//OnEndUsed - called from Ability component - abstract
	//IsBeingUsed(bool) - called from Ability component - abstract

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 Context;
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UAnimMontage* AbilityAnimMontage;

	UPROPERTY(EditAnywhere)
	FName AbilityName;

	UPROPERTY(EditAnywhere)
	int coolDownDuration = 3.f;
	UPROPERTY(EditAnywhere)
	int castDuration = 1.f;
	
	FTimerHandle CastTimerHandle; // Duration of ability
	FTimerHandle CoolDownTimerHandle; // Time to reset an ability
	
	bool IsBeingUsed();
	void EndCoolDown();
	void EndCastDuration();
	UAnimMontage* TryCast();
	virtual void CastAbility();

	virtual void OnAbilityDamage();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	TObjectPtr<AHeroCharacter> Player;
	UPROPERTY(EditAnywhere)
	UAnimInstance* AnimInstance;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
