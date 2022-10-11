// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

class UInventoryComponent;

// This class does not need to be modified.
UINTERFACE()
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIEVALRPG_API IItemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Send this to an item to add itself to the inventory provided
	 * @param Inventory Inventory to add items to 
	 * @return returns if picked up
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool TryAddItemToInventory(UInventoryComponent* Inventory);
};
