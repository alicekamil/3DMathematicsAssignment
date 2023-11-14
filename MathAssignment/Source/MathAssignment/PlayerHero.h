#pragma once

#include "CoreMinimal.h"
#include "Hero.h"
#include "InputActionValue.h"
#include "PlayerHero.generated.h"

class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class MATHASSIGNMENT_API APlayerHero : public AHero
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerHero();

private:
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraCrane;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	
protected:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	UCapsuleComponent* Capsule;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	void Move(const FInputActionValue& Value);

	void StartUseAbility(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(UIMin=0,UIMax=100))
	float Health;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="State", meta=(Bitmask, BitmaskEnum = "ERelativeContext"))
	int32 Context;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	TArray<AActor*> Players;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Context")
	bool DrawArc;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
