#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Unequipped UMETA(DisplayName = "Unequipped"),
	EquippedOneHandWeapon UMETA(DisplayName = "EquippedOneHandWeapon")
};