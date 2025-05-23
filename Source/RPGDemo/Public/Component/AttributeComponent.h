// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGDEMO_API UAttributeComponent : public UActorComponent {
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UAttributeComponent();
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Actor Attributes")
    float currrent_health_ = 100.0f;
    UPROPERTY(EditAnywhere, Category = "Actor Attributes")
    float max_health_ = 100.0f;
};