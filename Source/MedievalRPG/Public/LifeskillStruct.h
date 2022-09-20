// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "LifeskillStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLifeskillStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Level")
	int Level;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Xp")
	float CurrentXp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Xp")
	float MaxXp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Name")
	FText Name;

	TArray<FText> AllNames;

	void GenerateAllNames()
	{
		TArray<FString> StrNames = {"Holzhacken","Bergbau","Sammeln","Erhitzen","Schmieden","Kampf","Kochen","Herstellen"};
		AllNames.Init(FText(),8);
	
		for(int i = 0; i<StrNames.Num();i++)
		{
			AllNames[i] = FText::FromString(StrNames[i]);
		}
	}
	
	FLifeskillStruct(int LifeSkillID=0, int newLevel = 0, float newMaxXp = 0.0f, float newCurrentXp=0.0f)
	{
		GenerateAllNames();

		Level = newLevel;
		MaxXp = newMaxXp;
		CurrentXp = newCurrentXp;
		Name = AllNames[LifeSkillID];
	}
};