// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionSubsystem.h"
#include "PlayerEntity.h"
#include "HeroCharacter.h"
#include "IntersectionUtility.h"

void UIntersectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
}
//keep track of conditions

void UIntersectionSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		Demonstrator->Drawn = false;
	}
	
	Player->Drawn = false;
	
	if(IntersectionDemonstrators.Num() == 1)
	{
		IntersectionDemonstrators[0]->DrawShape(FColor::Green);
		return;
	}	

	if (Player)
	{
		for(const auto Demonstrator : IntersectionDemonstrators)
		{
			auto IntersectionTest = false;
			CurrentContext = UContextHelpers::GetRelativeContext(Player, Demonstrator);
			if(UContextHelpers::ContextPredicate(CurrentContext, ))
			// Perform the intersection test between Player and Demonstrator
			if(Player->IntersectionType == EIntersection::Sphere &&
				Demonstrator->IntersectionType == EIntersection::Sphere)
			{
				//
				auto ContactPoint = FVector();
				
				IntersectionTest = UIntersectionUtility::SphereSphere(
					Player->GetActorLocation(),
					Player->Radius,
					Demonstrator->GetActorLocation(),
					Demonstrator->Radius,
					ContactPoint
				);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);		
				}
			}

			if(Player->IntersectionType == EIntersection::Sphere &&
				Demonstrator->IntersectionType == EIntersection::Plane && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::SpherePlane(
					Player->GetActorLocation(),
					Player->Radius,
					Demonstrator->GetActorLocation(),
					Demonstrator->GetActorUpVector(),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(Player->IntersectionType == EIntersection::Ray &&
				Player->IntersectionType == EIntersection::Sphere && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RaySphere(
					Player->GetActorLocation(),
					Player->GetActorForwardVector(),
					Demonstrator->GetActorLocation(),
					Demonstrator->Radius,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(Player->IntersectionType == EIntersection::Ray && 
				Demonstrator->IntersectionType == EIntersection::Plane && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayPlane(
					Player->GetActorLocation(),
					Player->GetActorForwardVector(),
					Demonstrator->GetActorUpVector(),
					Demonstrator->GetActorLocation(),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(Player->IntersectionType == EIntersection::Ray && 
				Demonstrator->IntersectionType == EIntersection::Triangle && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayTriangle(
					Player->GetActorLocation(),
					Player->GetActorForwardVector(),
					Demonstrator->GetActorTransform().TransformPosition(Demonstrator->V0),
					Demonstrator->GetActorTransform().TransformPosition(Demonstrator->V1),
					Demonstrator->GetActorTransform().TransformPosition(Demonstrator->V2),
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(Player->IntersectionType == EIntersection::Sphere &&
				Demonstrator->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				IntersectionTest = UIntersectionUtility::SphereAABB(
					Player->GetActorLocation(),
					Player->Radius,
					Demonstrator->GetActorLocation() + Demonstrator->Min,
					Demonstrator->GetActorLocation() + Demonstrator->Max
					);
			}			

			if(Player->IntersectionType == EIntersection::AABB &&
				Demonstrator->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::AABBIntersect(
					Player->GetActorLocation() + Player->Min,
					Player->GetActorLocation() + Player->Max,
					Demonstrator->GetActorLocation() + Demonstrator->Min,
					Demonstrator->GetActorLocation() + Demonstrator->Max,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}

			if(Player->IntersectionType == EIntersection::Ray &&
				Demonstrator->IntersectionType == EIntersection::AABB && !IntersectionTest)
			{
				FVector ContactPoint;
				
				IntersectionTest = UIntersectionUtility::RayAABB(
					Player->GetActorLocation(),
					Player->GetActorForwardVector(),
					Demonstrator->GetActorLocation() + Demonstrator->Min,
					Demonstrator->GetActorLocation() + Demonstrator->Max,
					ContactPoint
					);

				if(IntersectionTest)
				{
					DrawDebugPoint(
						GetWorld(),
						ContactPoint,
						25.f,
						FColor::Cyan
						);					
				}
			}			
			
			if(IntersectionTest)
			{
				Player->DrawShape(FColor::Red);
				Demonstrator->DrawShape(FColor::Red);
			}
		}
	}

	for(const auto Demonstrator : IntersectionDemonstrators)
	{
		bool bOnScreen;
		
		if(Demonstrator->IntersectionType == EIntersection::AABB)
		{
			bOnScreen = UIntersectionUtility::AABBOnScreen(
				Demonstrator->Min,
				Demonstrator->Max,
				PlayerControllerInstance
				);
		}
		else
		{
			bOnScreen = UIntersectionUtility::IsOnScreen(
				PlayerControllerInstance,
				Demonstrator->GetActorLocation()
				); 
		}
		
		if(bOnScreen)
		{
			DrawDebugLine(
				GetWorld(),
				PlayerControllerInstance->GetPawn()->GetActorLocation(),
				Demonstrator->GetActorLocation(),
				FColor::Emerald
				);
			
			DrawDebugPoint(
				GetWorld(),
				Demonstrator->GetActorLocation(),
				25.f,
				FColor::Emerald
				);
		}
		
		if(!Demonstrator->Drawn)
			Demonstrator->DrawShape(FColor::Green);
		if(!Player->Drawn)
			Player->DrawShape(FColor::Green);
	}	
}


void UIntersectionSubsystem::RegisterPlayerController(APlayerController* PlayerController)
{
	PlayerControllerInstance = PlayerController; 
}

void UIntersectionSubsystem::SetPlayerCharacter(AHeroCharacter* PlayerCharacter)
{
	Player = PlayerCharacter;
}

void UIntersectionSubsystem::RegisterDemonstrator(APlayerEntity* Demonstrator)
{
	if(!IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Add(Demonstrator);
}

void UIntersectionSubsystem::UnregisterDemonstrator(APlayerEntity* Demonstrator)
{
	if(IntersectionDemonstrators.Contains(Demonstrator))
		IntersectionDemonstrators.Remove(Demonstrator);
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return GetStatID();
}