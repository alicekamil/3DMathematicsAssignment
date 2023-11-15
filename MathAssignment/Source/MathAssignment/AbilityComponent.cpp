#include "AbilityComponent.h"
#include "ContextHelpers.h"


UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHeroCharacter>(GetOwner());

	for (TSubclassOf<AAbility> abilityType : AbilityTypes) // 
	{
		AAbility* ability = GetWorld()->SpawnActor<AAbility>(abilityType, FVector::Zero(), FRotator::ZeroRotator);
		Abilities.Add(ability);
		ability->SetOwner(GetOwner());
	}
	Player->GetAbilityContexts(Abilities);
}

void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	//if(Player->IsJumping)
		//return false;
	
	if(IsAnyAbilityBeingUsed())
	{
		return false;
	}
	return true;
	
}

void UAbilityComponent::StartAbility()
{
	if(!GetCanUseAbility())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cant use ability!"));
		return;
	}
	Abilities[0]->TryCast();
	UE_LOG(LogTemp, Warning, TEXT("Called trycast"));
	//
}


// Check if the bitmask to cast AoE = players current context bitmask
