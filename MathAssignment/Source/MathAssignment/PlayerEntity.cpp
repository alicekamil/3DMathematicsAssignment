// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerEntity.h"
#include "DrawDebugHelpers.h"
#include "IntersectionSubsystem.h"
#include "IntersectionUtility.h"
#include "ShapeDrawUtility.h"
#include "Constants.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerEntity::APlayerEntity()
{
	
	PrimaryActorTick.bCanEverTick = true;
}


// Called every frame
void APlayerEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector Cross = FVector::CrossProduct(GetActorForwardVector(), GetActorRightVector());

	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f, FColor::Red);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorRightVector() * 100.f, FColor::Green);
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + Cross * 100.f, FColor::Blue);
	
	if(!DrawArc)
		return;
	
	DrawDebugCone(
		GetWorld(),
		GetActorLocation(),
		GetActorForwardVector(),
		CONST_Range,
		FMath::DegreesToRadians(CONST_Angle * .5f),
		0.f,
		1,
		FColor::Green
		);
}

void APlayerEntity::BeginPlay()
{
	Super::BeginPlay();

	//UPrimitiveComponent::SetRenderCustomDepth(2);

	const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
	SubSystem->RegisterEnemy(this);
}

void APlayerEntity::DrawShape(const FColor Color)
{
	if(Drawn) return;
	
	Drawn = true;
	
	const auto Location = GetActorLocation();
	const auto WorldContext = GetWorld();
	
	switch(IntersectionType.GetValue())
	{
	case EIntersection::Sphere:
		UShapeDrawUtility::Sphere(WorldContext, Location, Radius, Color);
		break;

	case EIntersection::Plane:
		UShapeDrawUtility::Plane(WorldContext, Location, GetActorUpVector(), GetActorQuat(), Color);
		break;
	
	case EIntersection::AABB:
		UShapeDrawUtility::Box(WorldContext, Location, Min, Max, Color);
		break;

	case EIntersection::Triangle:
		UShapeDrawUtility::Triangle(WorldContext, GetActorTransform(), V0, V1, V2, Color);
		break;

	case EIntersection::Ray:
		UShapeDrawUtility::Ray(WorldContext, GetActorLocation(), GetActorForwardVector(), Color);
		break;		
	}
}

void APlayerEntity::CheckInteresction()
{
	if (IntersectionType == AABB)
	{
		// Get the player controller
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PlayerController)
			return;

		// Get the mouse position
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);

		// Get the world location and direction from the mouse position
		FVector WorldLocation, WorldDirection;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

		// Perform the AABB-ray intersection
		FVector ContactPoint;
		bool bIntersects = UIntersectionUtility::RayAABB(WorldLocation, WorldDirection, Min, Max, ContactPoint);

		// If there is an intersection, handle it (you can replace this with your logic)
		if (bIntersects)
		{
			// Do something with the intersection
			// For example, change the color, play a sound, etc.
			UE_LOG(LogTemp, Warning, TEXT("AABB Intersection!"));
		}
	}
}




