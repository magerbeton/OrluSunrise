// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MoneyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMoneyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UPurseComponent;

class MEDIEVALRPG_API IMoneyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief 
	 * @param From Remove the money from this purse
	 * @param Amount How much to transfer
	 * @return 
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool TransferMoneyTo(UPurseComponent* From, float Amount);
};
