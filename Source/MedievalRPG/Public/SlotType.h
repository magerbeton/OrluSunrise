#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESlotType : uint8 {
	InventorySlot = 0 UMETA(DisplayName="ItemSlot"),
	EquipmentSlot = 1 UMETA(DisplayName="EquipmentSlot")
};

