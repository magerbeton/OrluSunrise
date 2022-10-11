// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEDIEVALRPG_API IDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Damage")
	void Damage(AActor* InflictingActor, float Amount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Damage")
	void MovementDebuff(AActor* InflictingActor, bool HeavyHit, bool SmackDown);
};
