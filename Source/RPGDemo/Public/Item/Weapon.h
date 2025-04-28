// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

class UBoxComponent;
/**
 *
 */
UCLASS()
class RPGDEMO_API AWeapon : public AItem {
    GENERATED_BODY()

public:
    AWeapon();

    UFUNCTION(BlueprintCallable)
    void setWeaponCollisionEnabled(ECollisionEnabled::Type collision_enabled);

protected:
    void BeginPlay() override;

    void onSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult& SweepResult) override;

    void onSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

    UFUNCTION()
    void onBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere)
    bool is_equipped = false;

    UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
    UBoxComponent* trace_box_component_ = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
    USceneComponent* box_trace_start_ = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Weapon Trace")
    USceneComponent* box_trace_end_ = nullptr;
};
