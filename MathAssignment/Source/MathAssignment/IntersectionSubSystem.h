
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "IntersectionSubsystem.generated.h"

class AHeroCharacter;
class APlayerEntity;

UCLASS()
class MATHASSIGNMENT_API UIntersectionSubsystem
	: public UTickableWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<APlayerEntity*> IntersectionDemonstrators;

	UPROPERTY()
	APlayerController* PlayerControllerInstance;

	UPROPERTY()
	AHeroCharacter* Player;
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	void RegisterPlayerController(APlayerController* PlayerController);
	void SetPlayerCharacter(AHeroCharacter* PlayerCharacter);
	
	void RegisterDemonstrator(APlayerEntity* Demonstrator);
	void UnregisterDemonstrator(APlayerEntity* Demonstrator);

	virtual TStatId GetStatId() const override;
};