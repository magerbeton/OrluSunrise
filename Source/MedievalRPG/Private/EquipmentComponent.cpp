// All Copyright belongs to Konstantin Passig

#include "EquipmentComponent.h"
#include "InventoryComponent.h"



// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	const ConstructorHelpers::FObjectFinder<UItemsDatabase>ItemsDatabaseObj(TEXT("ItemsDatabase'/Game/Data/DB_Items.DB_Items'"));
	if(ItemsDatabaseObj.Succeeded())
	{
		ItemsDatabase = ItemsDatabaseObj.Object;
	}

	// OnUpdate GearTypeEnum.h: change to new last element to add the new slot to the equipment system.
	EquippedItems.Init(FReducedItemStruct(), static_cast<uint8>(EEquipmentType::Armor_Accessory2));

}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEquipmentComponent::EquipItem(FReducedItemStruct Item, EEquipmentType SlotTypeDroppedOn)
{
	const FItemStruct FullItem = ItemsDatabase->GetItemByID(Item.ID);
	if(FullItem.EquipmentType == SlotTypeDroppedOn)
	{
		EquippedItems[static_cast<uint8>(SlotTypeDroppedOn)] = Item;
		OnEquipmentUpdated.Broadcast(SlotTypeDroppedOn);
		return true;
	}
	return false;
}

/**
 * @brief Allows to unequip an item when the slot is not empty 
 * @param InventoryToAddTo The target inventory where the item from the slot should be added to
 * @param EquipmentSlot The slot from which the item should get unequipped from
 * @return Was the operation successful?
 */
bool UEquipmentComponent::UnequipItem(UInventoryComponent* InventoryToAddTo, EEquipmentType EquipmentSlot)
{
	if(!EquippedItems.IsValidIndex(static_cast<uint8>(EquipmentSlot)))
	{
		return false;
	}
	
	if(EquippedItems[static_cast<uint8>(EquipmentSlot)].ID == 0)
	{
		return false;
	}

	if(InventoryToAddTo->IsValidLowLevel())
	{
		InventoryToAddTo->AddItemToInventory(EquippedItems[static_cast<uint8>(EquipmentSlot)]);
		return true;
	}
	return false;
}

