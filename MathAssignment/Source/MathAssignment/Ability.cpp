
#include "Ability.h"


//cooldown

//conditions, like collision and bitmask comparing

//spawning, vfx, yadayada

AAbility::AAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

//

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

	Cast();

	TimerManager.SetTimer(CoolDownTimerHandle, this, &AAbility::EndCoolDown, coolDownDuration, true);
	
}

void AAbility::Cast()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(CastTimerHandle, this, &AAbility::EndCastDuration, castDuration, true);
	
	UE_LOG(LogTemp, Warning, TEXT("Im getting casted:>>"));
}

void AAbility::BeginPlay()
{
	Super::BeginPlay();
	
	//const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
	
}

void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

