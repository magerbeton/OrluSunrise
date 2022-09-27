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
	WoodChopping = 0		UMETA(DisplayName="Holzhacken"),
	Mining = 1				UMETA(DisplayName="Bergbau"),
	Gathering = 2			UMETA(DisplayName="Sammeln"),
	Heating = 3				UMETA(DisplayName="Erhitzen"),
	Smithing = 4			UMETA(DisplayName="Schmieden"),
	Combat = 5				UMETA(DisplayName="Kampf"),
	Cooking = 6				UMETA(DisplayName="Kochen"),
	Crafting = 7			UMETA(DisplayName="Herstellen")
	
};