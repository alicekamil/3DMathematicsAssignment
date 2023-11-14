
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "HeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
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
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraCrane;
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;
	
protected:

	//UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	//USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* HeroMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* UseAbilityAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	void Move(const FInputActionValue& Value);

	void StartUseAbility(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
