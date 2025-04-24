// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "DemoCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class RPGDEMO_API ADemoCharacter : public ACharacter {
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ADemoCharacter();


    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    void move(const FInputActionValue& input_value);

    void look(const FInputActionValue& input_value);

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* movement_input_context_ = nullptr;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* movement_action_ = nullptr;
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* look_action_ = nullptr;

    UPROPERTY(EditAnywhere, Category = "Camera")
    USpringArmComponent* spring_arm_component_ = nullptr;
    UPROPERTY(EditAnywhere, Category = "Camera")
    UCameraComponent* camera_component_ = nullptr;
};
