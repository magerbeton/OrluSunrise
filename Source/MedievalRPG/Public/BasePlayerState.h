// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ExperienceInterface.h"
#include "ItemInterface.h"
#include "MoneyInterface.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"


class UInventoryComponent; class ULevelComponent; class UEquipmentComponent;
/**
 * 
 */
UCLASS()
class MEDIEVALRPG_API ABasePlayerState : public APlayerState, public IExperienceInterface
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UInventoryComponent* Inventory;

	UPROPERTY()
	UEquipmentComponent* Equipment;
	
	UPROPERTY()
	ULevelComponent* Levels;

	UPROPERTY()
	UPurseComponent* Purse;

	/**
	 * @brief Implementation of the Experience interface
	 * @param XpType Type of xp to add
	 * @param XpAmount Amount of xp to add
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddXpToSkill(EXpTypeEnum XpType, float XpAmount);
	virtual void AddXpToSkill_Implementation(EXpTypeEnum XpType, float XpAmount);

};
