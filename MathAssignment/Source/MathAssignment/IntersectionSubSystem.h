
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ContextHelpers.h"
#include "IntersectionSubsystem.generated.h"

class AHeroCharacter;
class APlayerEntity;

UCLASS()
class MATHASSIGNMENT_API UIntersectionSubsystem
	: public UTickableWorldSubsystem
{
	GENERATED_BODY()

	
	UPROPERTY()
	TArray<APlayerEntity*> Enemies;

	UPROPERTY()
	APlayerController* PlayerControllerInstance;

	UPROPERTY()
	AHeroCharacter* Player;

	TArray<int32> abilityContexts;

	
	
public:

	UPROPERTY()
	int32 CurrentContext;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	void RegisterPlayerController(APlayerController* PlayerController);
	void SetPlayerCharacter(AHeroCharacter* PlayerCharacter);
	
	void RegisterEnemy(APlayerEntity* Enemy);
	void UnregisterEnemy(APlayerEntity* Enemy);

	virtual TStatId GetStatId() const override;
};