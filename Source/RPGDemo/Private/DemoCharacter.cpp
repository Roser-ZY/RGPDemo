// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Components/CapsuleComponent.h"
#include "Item/Weapon.h"

// Sets default values
ADemoCharacter::ADemoCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the default behavior.
	// Do not rotate the character with the controller.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Rotate to the movement direction.
	UCharacterMovementComponent* character_movement = GetCharacterMovement();
	character_movement->bOrientRotationToMovement = true;
	character_movement->RotationRate = FRotator(0.0f, 400.0f, 0.0f);

	// Create components.
	spring_arm_component_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	spring_arm_component_->SetupAttachment(RootComponent);
	spring_arm_component_->TargetArmLength = 300.0f;
	// Let the spring arm rotate with the controller of this character.
	spring_arm_component_->bUsePawnControlRotation = true;

	camera_component_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera_component_->SetupAttachment(spring_arm_component_);

	hair_component_ = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	hair_component_->SetupAttachment(GetMesh());
	hair_component_->AttachmentName = FString("head");

	eyebrows_component_ = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	eyebrows_component_->SetupAttachment(GetMesh());
	eyebrows_component_->AttachmentName = FString("head");
}

// Called when the game starts or when spawned
void ADemoCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Binde delegates.
	UCapsuleComponent* capsule_component = GetCapsuleComponent();
	if (capsule_component)
	{
		capsule_component->OnComponentBeginOverlap.AddDynamic(this, &ADemoCharacter::onCapsuleBeginOverlap);
		capsule_component->OnComponentEndOverlap.AddDynamic(this, &ADemoCharacter::onCapsuleEndOverlap);
	}

	// Add the input mapping context.
	if (input_mapping_context_)
	{
		APlayerController* player_controller = Cast<APlayerController>(Controller);
		if (player_controller)
		{
			// Get the enhanced input subsystem and set the movement input context.
			// Note: This mapping context will be set in UE5 Editor.
			UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<
				UEnhancedInputLocalPlayerSubsystem>(
				player_controller->GetLocalPlayer());
			if (subsystem)
			{
				subsystem->AddMappingContext(input_mapping_context_, 0);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input mapping context is not set."));
	}
}

void ADemoCharacter::move(const FInputActionValue& input_value)
{
	if (Controller && input_value.IsNonZero())
	{
		// Get the yaw rotation value of the controller.
		// Note: GetControlRotation() will return the rotation of the controller in the world.
		// Note: The X axis is the forward direction of the controller.
		const FRotator yaw_rotation(0.0f, GetControlRotation().Yaw, 0.0f);

		const FVector forward_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		const FVector right_direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

		// Move.
		const FVector2D movement_vector = input_value.Get<FVector2D>();
		AddMovementInput(forward_direction, movement_vector.Y);
		AddMovementInput(right_direction, movement_vector.X);

		// UE_LOG(LogTemp, Display, TEXT("Forward: %f, Right: %f"), movement_vector.Y, movement_vector.X);
	}
}

void ADemoCharacter::look(const FInputActionValue& input_value)
{
	const FVector2D look_vector = input_value.Get<FVector2D>();
	AddControllerPitchInput(look_vector.Y);
	AddControllerYawInput(look_vector.X);
}

void ADemoCharacter::jump(const FInputActionValue& input_value)
{
	const bool is_jumping = input_value.Get<bool>();
	if (is_jumping)
	{
		Jump();
	}
}

void ADemoCharacter::onCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWeapon* weapon = Cast<AWeapon>(OtherActor);
	if (weapon)
	{
		current_state_ = ECharacterState::EquippedOneHandWeapon;
		GEngine->AddOnScreenDebugMessage(0, 30, FColor::Cyan, TEXT("Demo character equip the weapon."));
	}
}

void ADemoCharacter::onCapsuleEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ADemoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	bool input_actions_are_all_ready = movement_action_ && look_action_ && jump_action_;
	if (input_actions_are_all_ready)
	{
		UEnhancedInputComponent* enhanced_input_component = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
		if (enhanced_input_component)
		{
			enhanced_input_component->BindAction(movement_action_, ETriggerEvent::Triggered, this, &ADemoCharacter::move);
			enhanced_input_component->BindAction(look_action_, ETriggerEvent::Triggered, this, &ADemoCharacter::look);
			enhanced_input_component->BindAction(jump_action_, ETriggerEvent::Triggered, this, &ADemoCharacter::jump);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input actions are not all ready."));
	}
}
