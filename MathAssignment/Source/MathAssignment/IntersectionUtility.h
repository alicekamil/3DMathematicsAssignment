// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "IntersectionUtility.generated.h"

UCLASS()
class MATHASSIGNMENT_API UIntersectionUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Point OnScreen Test
	UFUNCTION(BlueprintCallable, Category = "Viewport Tests")
	static bool IsOnScreen(
		const APlayerController* PlayerController,
		const FVector& WorldPosition,
		const float ScreenSpaceCompare = 0.75f)
	{
		FVector2D ScreenPosition;
		UGameplayStatics::ProjectWorldToScreen(PlayerController, WorldPosition, ScreenPosition);

		int32 ScreenHeight, ScreenWidth;
		PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);

		return (ScreenPosition.X > ScreenSpaceCompare && ScreenPosition.X < ScreenWidth - ScreenSpaceCompare) &&
			(ScreenPosition.Y > ScreenSpaceCompare && ScreenPosition.Y < ScreenHeight - ScreenSpaceCompare);
	}

	// AABB OnScreen Test
	UFUNCTION(BlueprintCallable, Category = "Viewport Tests")
	static bool AABBOnScreen(
		const FVector Min,
		const FVector Max,
		const APlayerController* PlayerController,
		const float ScreenCompare = 0.75f)
	{
		return IsOnScreen(PlayerController, Min, ScreenCompare)
			&& IsOnScreen(PlayerController, Max, ScreenCompare);
	}	
	
	// Sphere-Sphere Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereSphere(
		const FVector CenterA,
		const float RadiusA,
		const FVector CenterB,
		const float RadiusB,
		FVector& ContactPoint)
	{
		const auto Diff = CenterA - CenterB;
		const auto RadiusSum = RadiusA + RadiusB;

		const auto bIntersects = Diff.Dot(Diff) <= RadiusSum * RadiusSum;

		if(bIntersects)
		{
			const auto Direction = CenterB - CenterA;
			RaySphere(CenterA, Direction.GetSafeNormal(), CenterB, RadiusB, ContactPoint);
		}

		return bIntersects;
	}

	// Sphere-Plane Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SpherePlane(
		const FVector Center,
		const float Radius,
		const FVector PlaneCenter,
		const FVector PlaneNormal,
		FVector& ContactPoint)
	{
		const auto Distance = Center.Dot(PlaneNormal) - PlaneNormal.Dot(PlaneCenter);
		const auto bIntersects = FMath::Abs(Distance) <= Radius;

		if(bIntersects)
		{
			RayPlane(Center, -PlaneNormal, PlaneNormal, PlaneCenter, ContactPoint);
		}
		
		return bIntersects;
	}

	// Line-Sphere Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RaySphere(
		const FVector Origin,
		const FVector Direction,
		const FVector Center,
		const float Radius,
		FVector& ContactPoint)
	{
		const auto W = Center - Origin;
		const auto WSQ = W.Dot(W);
		const auto Projection = W.Dot(Direction);
		const auto RSQ = Radius * Radius;

		// If sphere is behind ray, no intersection
		if(Projection < 0.f && WSQ > RSQ)
			return false;

		const auto VSQ = Direction.Dot(Direction);

		// Diff vs radius
		const auto bIntersects = (VSQ * WSQ - Projection * Projection <= VSQ * Radius * Radius);

		if(bIntersects)
		{
			const auto B = 2.f * Projection;
			const auto C = WSQ - Radius * Radius;
			const auto Discriminant = B * B - 4 * VSQ * C;
			const auto T = (B - FMath::Sqrt(Discriminant)) / (2.f * VSQ);

			if(Discriminant < 0)
				ContactPoint = Origin + (Direction * -1.f);
			else
				ContactPoint = Origin + (Direction * T);
		}
		
		return bIntersects;
	}

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool PointAABB(
		const FVector Point,
		const FVector Min,
		const FVector Max)
	{
		if(Point.X > Max.X || Min.X > Point.X)
			return false;

		if(Point.Y > Max.Y || Min.Y > Point.Y)
			return false;

		if(Point.Z > Max.Z || Min.Z > Point.Z)
			return false;
		
		return true;
	}

	// AABB-AABB Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool AABBIntersect(
		const FVector MinA,
		const FVector MaxA,
		const FVector MinB,
		const FVector MaxB,
		FVector& ContactPoint)
	{
		if(MinA.X > MaxB.X || MinB.X > MaxA.X)
			return false;

		if(MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
			return false;

		if(MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
			return false;

		const auto CenterA = (MinA + MaxA) / 2;
		const auto CenterB = (MinB + MaxB) / 2;
		const auto Direction = CenterB - CenterA;
		
		RayAABB(CenterA, Direction.GetSafeNormal(), MinB, MaxB, ContactPoint);

		return true;
	}

	// Sphere-AABB Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool SphereAABB(
		const FVector Origin,
		const float Radius,
		const FVector Min,
		const FVector Max)
	{
		auto SquareDistance = 0.f;

		if(Origin.X < Min.X)
			SquareDistance += (Min.X - Origin.X) * (Min.X - Origin.X);

		if(Origin.X > Max.X)
			SquareDistance += (Origin.X - Max.X) * (Origin.X - Max.X);

		if(Origin.Y < Min.Y)
			SquareDistance += (Min.Y - Origin.Y) * (Min.Y - Origin.Y);

		if(Origin.Y > Max.Y)
			SquareDistance += (Origin.Y - Max.Y) * (Origin.Y - Max.Y);

		if(Origin.Z < Min.Z)
			SquareDistance += (Min.Z - Origin.Z) * (Min.Z - Origin.Z);

		if(Origin.Z > Max.Z)
			SquareDistance += (Origin.Z - Max.Z) * (Origin.Z - Max.Z);

		return SquareDistance <= Radius * Radius;
	}

	// Ray-AABB Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayAABB(
		const FVector Origin,
		const FVector Direction,
		const FVector Min,
		const FVector Max,
		FVector& ContactPoint)
	{
		const auto T1 = (Min.X - Origin.X) / Direction.X;
		const auto T2 = (Max.X - Origin.X) / Direction.X;
		const auto T3 = (Min.Y - Origin.Y) / Direction.Y;
		const auto T4 = (Max.Y - Origin.Y) / Direction.Y;
		const auto T5 = (Min.Z - Origin.Z) / Direction.Z;
		const auto T6 = (Max.Z - Origin.Z) / Direction.Z;

		// Find the largest minimum value
		const auto TMin = FMath::Max(
			FMath::Max(
				FMath::Min(T1,T2),
				FMath::Min(T3,T4)
				),
			FMath::Min(T5,T6)
			);

		// Find the smallest maximum value
		const auto TMax = FMath::Min(
			FMath::Min(
				FMath::Max(T1,T2),
				FMath::Max(T3,T4)
				),
			FMath::Max(T5,T6)
			);

		if(TMax < 0 || TMin > TMax)
			return false;

		const auto T = TMin < 0.f ? TMax : TMin;

		ContactPoint = Origin + (Direction * T);

		return true;
	}

	// Ray-Plane Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayPlane(
		const FVector Origin,
		const FVector Direction,
		const FVector PlaneNormal,
		const FVector PlaneOrigin,
		FVector& ContactPoint)
	{
		const auto CoordDot = PlaneNormal.Dot(PlaneOrigin);
		const auto DirectionDot = PlaneNormal.Dot(Direction);

		// Skip if plane normal and ray share direction.
		if(DirectionDot >= 0)
		{
			return false;
		}

		const auto T = (CoordDot - PlaneNormal.Dot(Origin)) / DirectionDot;
		ContactPoint = Origin + Direction.GetSafeNormal() * T;
		
		return true;
	}

	// Ray-Triangle Intersection
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool RayTriangle(
		const FVector Origin,
		const FVector Direction,
		const FVector V0,
		const FVector V1,
		const FVector V2,
		FVector& ContactPoint)
	{
		const FVector E1 = V1 - V0;
		const FVector E2 = V2 - V0; 

		const auto P = Direction.Cross(E2);
		const auto A = E1.Dot(P);

		// No intersection or infinite intersections
		if(FMath::IsNearlyEqual(A, 0.f))
			return false;

		const auto F = 1.f / A;
		const auto S = Origin - V0;
		const auto U = F * S.Dot(P);

		// Outside triangle bounds on U axis.
		if(U < 0.f || U > 1.f)
			return false;

		const auto Q = S.Cross(E1);
		const auto V = F * Direction.Dot(Q);

		// Outside triangle bounds V axis (remove 'U +' to check quad instead of triangle).
		if(V < 0.f || U + V > 1.f)
			return false;

		const auto T = F * E2.Dot(Q);

		ContactPoint = Origin + (Direction * T);
		
		return T >= 0.f;
	}
};
