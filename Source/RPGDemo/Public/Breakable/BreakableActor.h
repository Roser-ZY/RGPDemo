// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

UCLASS()
class RPGDEMO_API ABreakableActor : public AActor, public IHitInterface {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABreakableActor();
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void getHit_Implementation(const FVector& impact_point) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UGeometryCollectionComponent> geometry_collection_;
};
