// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAbility.h"



// Sets default values
AMeleeAbility::AMeleeAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMeleeAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeleeAbility::CastAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("inside melee:>>"));
	
	//if(AbilityAnimMontage)
	//{
		//Player->PlayAnimMontage(AbilityAnimMontage, 1, NAME_None);
	//}
	//else UE_LOG(LogTemp, Warning, TEXT("didnt play montage inside melee:>>"));
	//AnimInstance->Montage_JumpToSection(NAME_None, AbilityAnimMontage);
}


// Called every frame
void AMeleeAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

