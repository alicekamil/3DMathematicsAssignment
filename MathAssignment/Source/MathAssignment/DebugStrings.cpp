#include "DebugStrings.h"

#include "PlayerEntity.h"
#include "ContextHelpers.h"
#include "Engine/Canvas.h"

void FDebugTextDelegateHelper::DrawDebugLabels(UCanvas* Canvas, APlayerController* PlayerController)
{
	if(!Canvas)
		return;

	const auto OldDrawColor = Canvas->DrawColor;
	Canvas->SetDrawColor(FColor::White);

	const auto View = Canvas->SceneView;
	const auto Font = GEngine->GetSmallFont();

	auto DebugText = DebugLabels.GetData();

	for(int32 i = 0; i < DebugLabels.Num(); i++, ++DebugText)
	{
		if(View->ViewFrustum.IntersectSphere(DebugText->Location, 1.f))
		{
			const auto ScreenLocation = Canvas->Project(DebugText->Location);
			Canvas->DrawText(Font, DebugText->Text, ScreenLocation.X, ScreenLocation.Y);
		}
	}

	Canvas->SetDrawColor(OldDrawColor);
}

void FDebugTextDelegateHelper::SetupFromProxy(const FDebugSceneProxy* InSceneProxy)
{
	DebugLabels.Reset();
	DebugLabels.Append(InSceneProxy->ProxyData.DebugLabels);
}

UDebugStrings::UDebugStrings(const FObjectInitializer& ObjectInitializer)
{
	FEngineShowFlags::RegisterCustomShowFlag(TEXT("DebugText"), false, SFG_Normal, FText::FromString("Debug Text"));
}

FDebugRenderSceneProxy* UDebugStrings::CreateDebugSceneProxy()
{
	FDebugSceneProxyData ProxyData;

	ProxyData.DebugLabels.Reset();

	if(const auto PlayerEntity = Cast<APlayerEntity>(GetOwner()))
	{
		for(const auto Actor : PlayerEntity->Players)
		{
			if(const auto OtherPlayer = Cast<APlayerEntity>(Actor))
			{
				if(PlayerEntity == OtherPlayer)
					continue;
				
				const auto RelativeContext = UContextHelpers::GetRelativeContext(PlayerEntity, OtherPlayer);

				if(UContextHelpers::ContextPredicate(RelativeContext, PlayerEntity->Context))
				{
					const auto Item = FDebugText(
						OtherPlayer->GetActorLocation(),
						FString("Match")
					);
		
					ProxyData.DebugLabels.Add(Item);
				}
				else
				{
					const auto ContextString = UEnum::GetValueOrBitfieldAsString(static_cast<ERelativeContext>(RelativeContext));
					
					const auto Item = FDebugText(
						OtherPlayer->GetActorLocation(),
						ContextString
					);
		
					ProxyData.DebugLabels.Add(Item);
				}
			}
		}
	}
	else
	{
		const auto Item = FDebugText(
			GetOwner()->GetActorLocation(),
			GetOwner()->GetName()
			);
		
		ProxyData.DebugLabels.Add(Item);
	}

	const auto NewSceneProxy = new FDebugSceneProxy(this, &ProxyData);
	DebugDrawDelegateManager.SetupFromProxy(NewSceneProxy);

	return NewSceneProxy;
}

FBoxSphereBounds UDebugStrings::CalcBounds(const FTransform& LocalToWorld) const
{
	const auto Box = FBox(
		FVector(-1000, -1000, -1000),
		FVector(1000, 1000, 1000)
	);

	return FBoxSphereBounds(Box);
}

