#include "AbilityComponent.h"
#include "ContextHelpers.h"
#include "IntersectionSubSystem.h"
#include "Engine/GameInstance.h"


UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHeroCharacter>(GetOwner());

	for (TSubclassOf<AAbility> abilityType : AbilityTypes)
	{
		AAbility* ability = GetWorld()->SpawnActor<AAbility>(abilityType, FVector::Zero(), FRotator::ZeroRotator);
		Abilities.Add(ability);
		ability->SetOwner(GetOwner());
	}
	GetAbilityContexts(Abilities);
}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAbilityComponent::GetAbilityContexts(TArray<AAbility*> ContextAbilities) 
{
	int i = 0;
	for(auto ability : ContextAbilities)
	{
		int32 abilityContext = ContextAbilities[i]->Context;
		abilityContexts.Add(abilityContext); //Store a list of all the abilities contexts 
		i++;
	}
}

bool UAbilityComponent::IsAnyAbilityBeingUsed()
{
	for(auto ability : Abilities)
	{
		if(ability->IsBeingUsed())
		{
			return true;
		}
	}
	return false;
}

//If _Any_ of the abilites has an active cast timer
bool UAbilityComponent::GetCanUseAbility()
{
	if(IsAnyAbilityBeingUsed())
	{
		return false;
	}
	return true;
}

void UAbilityComponent::StartAbility(int index)
{
	if(!GetCanUseAbility())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant use ability!"));
		return;
	}
	if(UContextHelpers::ContextPredicate(Player->SubSystem->CurrentContext, Abilities[index]->Context))
	{
		currAbility = Abilities[index];
		if(auto properties = Abilities[index]->TryCast(); properties.AbilityAnimMontage) //?
		{
			Player->PlayAnimMontage(properties.AbilityAnimMontage, 1, NAME_None);
			Player->SetLookAtCursor();
			Player->SetCharacterMobility(false);
			
			//In anim montage event - Player->SetCharacterMobility(true);
			
			//SpawnInitVFX(properties.InitVFX);
			//Look at cursor(player)
			//Player is immobile(player)
			//The montage abilityStart = Plays VFX(ability? but it passes it from the struct so maybe here?)
			//The montage Damage(enemy?)
			//The montage ability"End" = Ability

			//Questions to Martin:
			//1. Animation montage, how to play next "sequence..?" How does it work in general:>
			//2. How to "spawn" and "destroy" abilites when theyre init in start, object pooling, what is it that will be created and destroyed?
			//3. Setting up damage- collision, enemy?
			
		}
		UE_LOG(LogTemp, Warning, TEXT("Called trycast"));
	}
	
}

