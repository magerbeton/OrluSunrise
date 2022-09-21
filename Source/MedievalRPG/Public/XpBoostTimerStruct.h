// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "XpBoostTimerStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FXpBoostTimerStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Time")
	float RemainingTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Xp")
	float XpBoost;
	
	FXpBoostTimerStruct(float newRemainingTime = 0, float newXpBoost = 0)
	{
		RemainingTime = newRemainingTime;
		XpBoost = newXpBoost;
	}
};