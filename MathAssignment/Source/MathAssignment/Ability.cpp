
#include "Ability.h"
#include "Animation/AnimMontage.h"
#include "FunctionalUIScreenshotTest.h"
#include "Kismet/GameplayStatics.h"


//cooldown

//conditions, like collision and bitmask comparing

//spawning, vfx

AAbility::AAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAbility::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AHeroCharacter>(GetOwner());
	if(Player)
	{
		AnimInstance = Player->GetMesh()->GetAnimInstance();
	}
}

bool AAbility::IsBeingUsed()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager(); //TODO: see if can make a reference?
	if(TimerManager.IsTimerActive(CastTimerHandle))
	{
		return true;
	}
	return false;
}

void AAbility::EndCoolDown()
{
	GetWorld()->GetTimerManager().ClearTimer(CoolDownTimerHandle);
	//Call event to make Icon green again
}

void AAbility::EndCastDuration()
{
	GetWorld()->GetTimerManager().ClearTimer(CastTimerHandle);
	//Reset freeze for things u cant do when casting a spell
}

void AAbility::TryCast()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if(TimerManager.IsTimerActive(CoolDownTimerHandle) || TimerManager.IsTimerActive(CastTimerHandle)) return;

	CastAbility();

	TimerManager.SetTimer(CoolDownTimerHandle, this, &AAbility::EndCoolDown, coolDownDuration, true);
	
}

void AAbility::CastAbility()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(CastTimerHandle, this, &AAbility::EndCastDuration, castDuration, true);

	Player->PlayAnimMontage(this->AbilityAnimMontage, 1, NAME_None);
	UE_LOG(LogTemp, Warning, TEXT("Im getting casted:>>"));
}	

void AAbility::OnAbilityDamage()
{
}


void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

