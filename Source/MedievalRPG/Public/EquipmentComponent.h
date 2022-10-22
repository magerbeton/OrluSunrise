// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "ReducedItemStruct.h"
#include "Components/ActorComponent.h"
#include "GearTypeEnum.h"
#include "EquipmentComponent.generated.h"

class UInventoryComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEquipmentUpdated, EEquipmentType, EquipmentSlot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEDIEVALRPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category="Items")
	TArray<FReducedItemStruct> EquippedItems;

	UFUNCTION(BlueprintCallable, Category="Items")
	bool EquipItem(FReducedItemStruct Item, EEquipmentType SlotTypeDroppedOn);

	UPROPERTY()
	UItemsDatabase* ItemsDatabase;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Items")
	FEquipmentUpdated OnEquipmentUpdated;

	UFUNCTION(BlueprintCallable, Category="Items")
	bool UnequipItem(UInventoryComponent* InventoryToAddTo, EEquipmentType EquipmentSlot);

	UFUNCTION(BlueprintCallable, Category="Items")
	void LogAllEquippedItems();

	UFUNCTION(BlueprintCallable, Category="Items")
	void LogSpecifiedItem(EEquipmentType ItemType);

	UFUNCTION(BlueprintCallable, Category="Items")
	FReducedItemStruct GetItemByType(EEquipmentType Equipment, bool& Success) const;
	
};
