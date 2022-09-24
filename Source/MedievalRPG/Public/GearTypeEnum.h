// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	// IMPORTANT: EVERYTIME THERE IS A CHANGE -> UPDATE THE ITEMS DATABASE WITH THE PY SCRIPT
	None = 0			UMETA(DisplayName="None"),
	Armor_Helmet = 1	UMETA(DisplayName="Helmet"),
	Armor_Chest = 2		UMETA(DisplayName="Chest"),
	Armor_Legs = 3		UMETA(DisplayName="Legs"),
	Armor_Foot = 4		UMETA(DisplayName="Boots"),
	Weapon_Blade = 5	UMETA(DisplayName="Klinge"),
	Weapon_Parry = 6	UMETA(DisplayName="Parierstange"),
	Weapon_Grip	= 7		UMETA(DisplayName="Griff"),
	Weapon_Pummel = 8	UMETA(DisplayName="Knauf"),
	Weapon_Rohling = 9	UMETA(DisplayName="Rohling"),
	Consumable = 10		UMETA(DisplayName="Consumable")
};