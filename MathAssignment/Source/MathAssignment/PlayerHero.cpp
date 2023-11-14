#include "PlayerHero.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputSubSystems.h"
#include "Constants.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"


// Sets default values
APlayerHero::APlayerHero()
{
	PrimaryActorTick.bCanEverTick = true;


	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	CameraCrane = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraCrane"));
	CameraCrane->SetupAttachment(RootComponent);
	CameraCrane->TargetArmLength = 2400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ViewCamera->SetupAttachment(CameraCrane);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
}

// Called when the game starts or when spawned
void APlayerHero::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) //TODO: Cast? Temporary pointer, freed up instantly.
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(HeroMappingContext, 0);
		}
	}
}

void APlayerHero::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if (Controller && DirectionValue != 0.f)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
}

void APlayerHero::StartUseAbility(const FInputActionValue& Value)
{
	const bool CurrentValue = Value.Get<bool>();
	if (CurrentValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability usage triggered"));
	}
}

void APlayerHero::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
	
}

// Called every frame
void APlayerHero::Tick(float DeltaTime)
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


// Called to bind functionality to input
void APlayerHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerHero::Move);
		EnhancedInputComponent->BindAction(UseAbilityAction, ETriggerEvent::Started, this, &APlayerHero::StartUseAbility);//TODO: Started/Triggered?
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerHero::Look);
		
	}

	
}

