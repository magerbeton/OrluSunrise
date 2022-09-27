// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIEVALRPG_API IPickupInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="TryPickup")
	bool TryPickup(UInventoryComponent* Inventory);
};
