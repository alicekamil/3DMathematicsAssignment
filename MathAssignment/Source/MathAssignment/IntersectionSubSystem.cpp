// Fill out your copyright notice in the Description page of Project Settings.
#include "IntersectionSubsystem.h"
#include "PlayerEntity.h"
#include "HeroCharacter.h"
#include "IntersectionUtility.h"

//Some form of target selection

void UIntersectionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UIntersectionSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	for(const auto Enemy : Enemies)
	{
		Enemy->Drawn = false;
	}
	
	Player->Drawn = false;
	
	if(Enemies.Num() == 1)
	{
		Enemies[0]->DrawShape(FColor::Green);
		return;
	}	

	if (Player)
	{
		// Get the mouse position
		float MouseX,MouseY;
		PlayerControllerInstance->GetMousePosition(MouseX, MouseY);

		//cursor from screen to world position
		// Get the world location and direction from the mouse position
		FVector WorldLocation, WorldDirection;
		PlayerControllerInstance->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		

		// Define the ray parameters
		FVector RayOrigin = WorldLocation;
		//APlayerCameraManager *camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
		//FVector camLocation = camManager->GetCameraLocation();
		//FVector camForward  = camManager->GetCameraRotation().Vector();
		//FVector RayOrigin = camLocation;
		FVector RayDirection = WorldDirection;
		//FVector RayDirection = camForward.GetSafeNormal();
		
		for(const auto Demonstrator : Enemies)
		{
			auto IntersectionTest = false;
			CurrentContext = UContextHelpers::GetRelativeContext(Player, Demonstrator); 

			FVector Min = Demonstrator->Min + Demonstrator->GetActorLocation();
			FVector Max = Demonstrator->Max + Demonstrator->GetActorLocation();
			
			FVector TestContactPoint;

			if(UIntersectionUtility::RayAABB(RayOrigin, RayDirection, Min, Max, TestContactPoint))
			{
				Demonstrator->StaticMeshComponent->SetCustomDepthStencilValue(3);
			}
			else
			{
				Demonstrator->StaticMeshComponent->SetCustomDepthStencilValue(1);
			}

			
			//if(UContextHelpers::ContextPredicate(CurrentContext, ))
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
					Demonstrator->StaticMeshComponent->SetCustomDepthStencilValue(0);
					Player->GetMesh()->SetCustomDepthStencilValue(253);
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

	for(const auto Demonstrator : Enemies)
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

void UIntersectionSubsystem::RegisterEnemy(APlayerEntity* Enemy)
{
	if(!Enemies.Contains(Enemy))
		Enemies.Add(Enemy);
}

void UIntersectionSubsystem::UnregisterEnemy(APlayerEntity* Enemy)
{
	if(Enemies.Contains(Enemy))
		Enemies.Remove(Enemy);
}

TStatId UIntersectionSubsystem::GetStatId() const
{
	return GetStatID();
}