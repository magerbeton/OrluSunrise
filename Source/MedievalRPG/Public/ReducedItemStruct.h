// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ReducedItemStruct.generated.h"

USTRUCT(BlueprintType)
struct FReducedItemStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int ID;

	UPROPERTY(BlueprintReadOnly, Category="Default")
	FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int Amount;

	FText GetItemName(int id)
	{
		return FText::FromString("Not finished!");
	}

	FString ItemAsString()
	{
		return FString::Printf(TEXT("ID: %i, Amount: %i, Name: %s"),ID,Amount,*Name.ToString());
	}

	FReducedItemStruct(int id = 0, int amount = 0)
	{
		ID = id;
		Amount = amount;
		Name = GetItemName(id);
	}
};
