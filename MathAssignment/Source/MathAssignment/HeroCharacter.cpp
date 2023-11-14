#include "HeroCharacter.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputSubSystems.h"
#include "Constants.h"
#include "ShapeDrawUtility.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "IntersectionSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator()
	
	//SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	CameraCrane = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraCrane"));
	CameraCrane->SetupAttachment(RootComponent);
	CameraCrane->TargetArmLength = 2400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(CameraCrane);

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

void AHeroCharacter::DrawShape(const FColor Color)
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

void AHeroCharacter::Jump()
{
	Super::Jump();
	
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) //TODO: Cast? Temporary pointer, freed up instantly.
	{
		const auto SubSystem = GetWorld()->GetSubsystem<UIntersectionSubsystem>();
		SubSystem->RegisterPlayerController(PlayerController);
		SubSystem->SetPlayerCharacter(this);
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(HeroMappingContext, 0);
		}
	}
}

void AHeroCharacter::Move(const FInputActionValue& Value)
{
	//ActionState != EActionState::EAS_Unoccupied) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//const FVector Forward = GetActorForwardVector();
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AHeroCharacter::StartUseAbility(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("ABILITY USED!"));
	}
}

void AHeroCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Move);
		EnhancedInputComponent->BindAction(UseAbilityAction, ETriggerEvent::Started, this, &AHeroCharacter::StartUseAbility);//TODO: Started/Triggered?
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Jump);
		
	}


}

