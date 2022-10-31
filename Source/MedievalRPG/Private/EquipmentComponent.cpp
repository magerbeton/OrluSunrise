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
	// get the full item information to confirm if it is allowed to go into the slot which it was dropped on
	const FItemStruct FullItem = ItemsDatabase->GetItemByID(Item.ID);
	if(FullItem.EquipmentType == SlotTypeDroppedOn)
	{
		// Item slot type is correct:
		// Set the Equipment Slot to the new item.
		EquippedItems[static_cast<uint8>(SlotTypeDroppedOn)] = Item;
		OnEquipmentUpdated.Broadcast(SlotTypeDroppedOn);
		return true;
	}
	UE_LOG(LogTemp,Display,TEXT("Dropped item on wrong slottype: %i"),static_cast<uint8>(SlotTypeDroppedOn));
	return false;
}

void UEquipmentComponent::LogAllEquippedItems()
{
	for (FReducedItemStruct& Item : EquippedItems)
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*Item.ItemAsString());
	}
}

void UEquipmentComponent::LogSpecifiedItem(EEquipmentType ItemType)
{
	if(EquippedItems.IsValidIndex(static_cast<uint8>(ItemType)))
	{
		UE_LOG(LogTemp,Display,TEXT("Item is: %s"),*EquippedItems[static_cast<uint8>(ItemType)].ItemAsString());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Item ItemType is not valid access id"));
	}
}

bool UEquipmentComponent::GetItemByType(EEquipmentType Equipment, FReducedItemStruct& Item) const
{
	if(!EquippedItems.IsValidIndex(static_cast<uint8>(Equipment)))
	{
		Item = FReducedItemStruct();
		return false;
	}
	Item = EquippedItems[static_cast<uint8>(Equipment)];
	return true;
}

bool UEquipmentComponent::IsSlotEmpty(EEquipmentType Type) const
{
	const FReducedItemStruct TempItem = EquippedItems[static_cast<uint8>(Type)];
	if(TempItem.ID == 0 || TempItem.Amount == 0)
	{
		return true;
	}
	return false;
}

void UEquipmentComponent::EmptySlot(EEquipmentType Type)
{
	EquippedItems[static_cast<uint8>(Type)] = FReducedItemStruct();
}
