// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "XpBoostStruct.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FXpBoostStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Time;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AddedBoost;

	FXpBoostStruct(float newTime = 0.0f, float newAddedBoost = 0.0f)
	{
		Time = 0;
		AddedBoost = 0;
	}
};
