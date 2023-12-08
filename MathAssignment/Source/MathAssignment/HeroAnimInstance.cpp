#include "HeroAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "HeroCharacter.h"
#include "Kismet/BlueprintTypeConversions.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<AHeroCharacter>(TryGetPawnOwner());
	if (Character)
	{
		AbilityComponent = Character->GetAbilityComponent();
		CharacterMovement = Character->GetCharacterMovement();
	}
	
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (CharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity); //TODO: calc?
		IsFalling = CharacterMovement->IsFalling();
	}
	
	
}
