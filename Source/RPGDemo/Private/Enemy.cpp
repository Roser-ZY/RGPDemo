// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Component/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AEnemy::AEnemy()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;

    // Set the attributes of collision.
    USkeletalMeshComponent* skeletal_mesh = GetMesh();
    if (skeletal_mesh == nullptr) {
        skeletal_mesh->SetCollisionObjectType(ECC_Visibility);
        skeletal_mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
        skeletal_mesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Block);
        skeletal_mesh->SetGenerateOverlapEvents(true);
        UCapsuleComponent* capsule_component = GetCapsuleComponent();
        if (capsule_component) {
            capsule_component->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
        }
    }

    attribute_component_ = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
    health_bar_widget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
    health_bar_widget_->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::getHit_Implementation(const FVector& impact_point)
{
    UE_LOG(LogTemp, Warning, TEXT("The enemy get hit."));
    if (anim_montage_ == nullptr) {
        return;
    }
    USkeletalMeshComponent* skeletal_mesh = GetMesh();
    if (skeletal_mesh == nullptr) {
        return;
    }
    UAnimInstance* anim_instance = skeletal_mesh->GetAnimInstance();
    if (anim_instance == nullptr) {
    }
    anim_instance->Montage_Play(anim_montage_);
}
