#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CollisionShape.h"
#include "Intersections.h"
#include "IntersectionSubSystem.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbilityComponent;
class UIntersectionSubsystem;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MATHASSIGNMENT_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHeroCharacter();

	virtual void Jump() override;

	UPROPERTY()
	UIntersectionSubsystem* SubSystem;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UFUNCTION(BlueprintCallable)
	UAbilityComponent* GetAbilityComponent();

	bool canMove = true;
	
	UFUNCTION()
	void SetLookAtCursor();
	UFUNCTION(BlueprintCallable)
	void SetCharacterMobility(bool isDone);

private:

	UPROPERTY(VisibleAnywhere)
	UAbilityComponent* AbilityComponent;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraCrane;
	
	float targetArmLength;

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAbilityOneAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAbilityTwoAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAbilityThreeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	UInputAction* CamZoomInAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	UInputAction* CamZoomOutAction;

	void Move(const FInputActionValue& Value);

	void StartAbility1(const FInputActionValue& Value);
	void StartAbility2(const FInputActionValue& Value);
	void StartAbility3(const FInputActionValue& Value);
	

	void Look(const FInputActionValue& Value);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EIntersection> IntersectionType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Sphere")
	float Radius = 500.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Min;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="AABB", meta = (MakeEditWidget = true))
	FVector Max;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Triangle", meta = (MakeEditWidget = true))
	FVector V2;

	UPROPERTY()
	bool Drawn;
	
	void DrawShape(const FColor Color);

	void CameraZoomIn();

	void CameraZoomOut();

	float desiredCamDistance = 2400.f;
	float zoomMin = 300.f;
	float zoomMax = 2500.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 Context;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Players;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;

	bool IsFalling;
	
	UPROPERTY(BlueprintReadOnly, Category = Spells)
	bool IsCurrentlyPlayingSpell = false;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

};
