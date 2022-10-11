#pragma once

#include "CoreMinimal.h"
#include "ReducedItemStruct.h"
#include "EnemyStruct.generated.h"

//this is faulty and causes the editor to crash!!!

USTRUCT(BlueprintType)
struct FEnemyStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Level;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* MaxHealthCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCurveFloat* XpCurve;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FReducedItemStruct> ItemsToDrop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Money;
	
	FORCEINLINE float GetXp(bool& Success) const;

	FORCEINLINE float GetMaxHealth(bool& Success) const;

	FEnemyStruct(int newLevel = 1, UCurveFloat* newMaxHealthCurve = nullptr, UCurveFloat* newXpCurve = nullptr, TArray<FReducedItemStruct> newItemsToDrop = {}, int newMoney = 0)
	{
		Level = newLevel;
		MaxHealthCurve = newMaxHealthCurve;
		XpCurve = newXpCurve;
		ItemsToDrop = newItemsToDrop;
		Money = newMoney;
	}
	
};

/**
 * @brief Returns the xp if a xp curve is specified
 * @param Success gives the return value credibility
 * @return Amount of Xp to gain when enemy is killed
 */
inline float FEnemyStruct::GetXp(bool& Success) const
{
	if(XpCurve == nullptr)
	{
		Success = false;
		return 0.0f;
	}

	Success = true;
	return XpCurve->GetFloatValue(static_cast<float>(Level));
}

inline float FEnemyStruct::GetMaxHealth(bool& Success) const
{
	if(MaxHealthCurve == nullptr)
	{
		Success = false;
		return 0.0f;
	}

	Success = true;
	return MaxHealthCurve->GetFloatValue(static_cast<float>(Level));
}
