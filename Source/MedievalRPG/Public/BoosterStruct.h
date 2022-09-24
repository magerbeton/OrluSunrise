// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "BoosterStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBoosterStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Variables")
	float RemainingTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Variables")
	float Boost;
	
	FBoosterStruct(float newRemainingTime = 0, float newBoost = 0)
	{
		RemainingTime = newRemainingTime;
		Boost = newBoost;
	}
};