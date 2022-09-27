// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "XpTypeEnum.h"
#include "UObject/Interface.h"
#include "ExperienceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UExperienceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIEVALRPG_API IExperienceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Experience")
	void AddXpToSkill(EXpTypeEnum XpType, float XpAmount);
};
