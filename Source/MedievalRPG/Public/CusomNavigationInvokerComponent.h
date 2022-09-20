// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "NavigationInvokerComponent.h"
#include "CusomNavigationInvokerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Navigation), meta = (BlueprintSpawnableComponent))
class MEDIEVALRPG_API UCusomNavigationInvokerComponent : public UNavigationInvokerComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetTileGenerationRadius(float Radius);

	UFUNCTION(BlueprintCallable)
	float GetTileGenerationRadius();

	UFUNCTION(BlueprintCallable)
	void SetTileRemovalRadius(float Radius);

	UFUNCTION(BlueprintCallable)
	float GetTileRemovalRadius();

	
};
