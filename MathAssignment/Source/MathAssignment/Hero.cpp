// Fill out your copyright notice in the Description page of Project Settings.

#include "Hero.h"

// Sets default values
AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

