// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ItemStruct.h"
#include "ReducedItemStruct.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UEquipmentComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangedItemSlot, int, index);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEDIEVALRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category="Inventory")
	int NumberOfSlots;
	
	UPROPERTY(BlueprintReadWrite, Category="Inventory")
	TArray<FReducedItemStruct> Inventory;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItemToInventory(FReducedItemStruct Item);

	bool FindItemInInventory(FReducedItemStruct Item, int& location);

	bool IsInventoryFull();

	UPROPERTY(BlueprintAssignable)
	FChangedItemSlot OnChangedItemSlot;

	UPROPERTY(BlueprintReadOnly, Category="Database")
	UItemsDatabase* ItemsDatabase;

	void Debug_PrintInventory();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Audio")
	UAudioComponent* AudioComponent;
	
	UPROPERTY()
	USoundBase* PickupSound;

	void PlayPickupSound() const;

	UFUNCTION(BlueprintCallable, Category="Equipment")
	bool PrepareSlotForEquip(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool ReduceItemFromSlot(int SlotIndex, int Amount);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void ClearSlot(int SlotIndex);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Inventory")
	bool GetItemById(int Index, FReducedItemStruct& Item);


	
	// Equipment related stuff
	
	UPROPERTY(BlueprintReadWrite)
	UEquipmentComponent* EquipmentComponent;

	UFUNCTION(BlueprintCallable)
	bool EquipItem(UEquipmentComponent* EquipmentCompRef, EEquipmentType Type, FReducedItemStruct Item);
	
	UFUNCTION(BlueprintCallable)
	bool UnequipItem(EEquipmentType Type);

	// Equipment related stuff end
};
