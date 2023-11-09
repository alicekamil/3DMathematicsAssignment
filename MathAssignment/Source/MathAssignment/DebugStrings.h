#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugDrawComponent.h"
#include "DebugStrings.generated.h"


struct FDebugText
{
	FVector Location;
	FString Text;

	FDebugText() {};
		
	FDebugText(const FVector& InLocation, const FString& InText)
		: Location(InLocation), Text(InText)
	{};
};

struct FDebugSceneProxyData
{
	TArray<FDebugText> DebugLabels;
};

class FDebugSceneProxy : public FDebugRenderSceneProxy
{
public:
	FDebugSceneProxy(const UPrimitiveComponent* InComponent, FDebugSceneProxyData* ProxyData)
		: FDebugRenderSceneProxy(InComponent)
	{
		DrawType = SolidAndWireMeshes;
		ViewFlagName = TEXT("DebugText");

		this->ProxyData = *ProxyData;

		for(const auto& Text : ProxyData->DebugLabels)
		{
			auto NewText = FText3d(
				Text.Text,
				Text.Location,
				FColor::White
				);
			
			this->Texts.Add(NewText);
		}
	}

	FDebugSceneProxyData ProxyData;
};

class FDebugTextDelegateHelper : public FDebugDrawDelegateHelper
{
public:
	virtual void DrawDebugLabels(UCanvas* Canvas, APlayerController*) override;

	void SetupFromProxy(const FDebugSceneProxy* InSceneProxy);

	TArray<FDebugText> DebugLabels;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MATHASSIGNMENT_API UDebugStrings : public UDebugDrawComponent
{
	GENERATED_BODY()

	UDebugStrings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;
	
	virtual FDebugDrawDelegateHelper& GetDebugDrawDelegateHelper() override
	{
		return DebugDrawDelegateHelper;		
	};

	virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;

	FDebugTextDelegateHelper DebugDrawDelegateManager;
};
