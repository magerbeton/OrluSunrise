// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ExecuteShellCommand.generated.h"

/**
 * 
 */
UCLASS()
class MEDIEVALRPG_API UExecuteShellCommand : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "execute"))
	static FString ExecuteCommand(FString cmd_raw);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "execute"))
		static void CloseConsole();
	
};
