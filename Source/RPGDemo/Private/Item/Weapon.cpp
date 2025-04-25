// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon.h"
#include "DemoCharacter.h"

void AWeapon::onSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	Super::onSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ADemoCharacter* demo_character = Cast<ADemoCharacter>(OtherActor);
	if (demo_character)
	{
		// Note: The AttachToComponent() is same as Attach Component To Component in Blueprint.
		FAttachmentTransformRules transform_rules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
		static_mesh_component_->AttachToComponent(demo_character->GetMesh(), transform_rules, FName("right_hand_socket"));
	}
}

void AWeapon::onSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::onSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
