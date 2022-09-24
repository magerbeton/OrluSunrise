// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "XpTypeEnum.generated.h"

/**
 * 
 */

// "Holzhacken","Bergbau","Sammeln","Erhitzen","Schmieden","Kampf","Kochen","Herstellen"

UENUM(BlueprintType)
enum class EXpTypeEnum : uint8
{
	None = 0				UMETA(DisplayName="None"),
	WoodChopping = 1		UMETA(DisplayName="Holzhacken"),
	Mining = 2				UMETA(DisplayName="Bergbau"),
	Gathering = 3			UMETA(DisplayName="Sammeln"),
	Heating = 4				UMETA(DisplayName="Erhitzen"),
	Smithing = 5			UMETA(DisplayName="Schmieden"),
	Combat = 6				UMETA(DisplayName="Kampf"),
	Cooking = 7				UMETA(DisplayName="Kochen"),
	Crafting = 8			UMETA(DisplayName="Herstellen")
	
};