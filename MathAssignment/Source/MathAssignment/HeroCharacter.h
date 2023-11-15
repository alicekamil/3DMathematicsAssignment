
#pragma once

//Input

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CollisionShape.h"
#include "Intersections.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAbilityComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MATHASSIGNMENT_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter();

	virtual void Jump() override;

private:

	TArray<int32> abilityContexts;

	UPROPERTY(VisibleAnywhere)
	UAbilityComponent* AbilityComponent;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraCrane;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAoEAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);

	void StartAbility1(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void GetAbilityContexts(TArray<AAbility*> Abilities);

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

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
