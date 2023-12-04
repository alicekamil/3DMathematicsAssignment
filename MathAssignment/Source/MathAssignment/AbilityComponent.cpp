#include "AbilityComponent.h"
#include "ContextHelpers.h"
#include "IntersectionSubSystem.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"


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
		if(auto castedAnimMontage = Abilities[index]->TryCast(); castedAnimMontage)
		{
			Player->PlayAnimMontage(castedAnimMontage, 1, NAME_None);
		}
			
			
		
		
		UE_LOG(LogTemp, Warning, TEXT("Called trycast"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Failed"));
}

