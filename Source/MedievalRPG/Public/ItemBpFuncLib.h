// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "ReducedItemStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ItemBpFuncLib.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MEDIEVALRPG_API UItemBpFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Transform")
	static FReducedItemStruct ItemToReducedItem(FItemStruct Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Transform")
	static FReducedItemStruct ItemToReducedItemCustomAmount(FItemStruct Item, int Amount);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Transform")
	static FString ItemToString(FItemStruct Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Transform")
	static FString ItemToStringExt(FItemStruct Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Export")
	static FString ItemToCopyableString(FItemStruct Item);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Path")
	static FString GetPathOfActor(UObject* Object);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="String")
	static FString RemoveAt(FString String, int index);
};
