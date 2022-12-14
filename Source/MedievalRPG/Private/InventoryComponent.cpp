// All Copyright belongs to Konstantin Passig


#include "InventoryComponent.h"

#include "EquipmentComponent.h"
#include "Components/AudioComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	NumberOfSlots = 24;
	Inventory.Init(FReducedItemStruct(),NumberOfSlots);

	const ConstructorHelpers::FObjectFinder<UItemsDatabase>ItemDatabaseObj(TEXT("ItemsDatabase'/Game/Data/DB_Items.DB_Items'"));
	if(ItemDatabaseObj.Succeeded())
	{
		ItemsDatabase = ItemDatabaseObj.Object;
	}

	const ConstructorHelpers::FObjectFinder<USoundBase>PickupSoundObj(TEXT("SoundCue'/Game/Sounds/ItemDroppedOnSlot/ItemDroppedOnSlot_Cue.ItemDroppedOnSlot_Cue'"));
	if(PickupSoundObj.Succeeded())
	{
		PickupSound = PickupSoundObj.Object;
	}
	

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// should never be used!
	// ...
}

bool UInventoryComponent::AddItemToInventory(FReducedItemStruct Item)
{
	if(Item.Amount <= 0 || Item.ID == 0)
	{
		// blocks the pickup of empty items
		UE_LOG(LogTemp,Warning,TEXT("Can't pickup item! Item Invalid!"));
		return false;
	}
	
	int index;
	if(FindItemInInventory(FReducedItemStruct(1,4),index))
	{
		UE_LOG(LogTemp,Display,TEXT("Item already is in inventory and can be stacked"));
		//item exists and can be stacked
		Inventory[index].Amount += Item.Amount;
		OnChangedItemSlot.Broadcast(index);
		PlayPickupSound();
		return true;
	}
	
	//item does not yet exist in inventory or the inventory is full
	//if inventory is full return false
	if(IsInventoryFull())
	{
		UE_LOG(LogTemp,Display,TEXT("Inventory is full and nothing can get picked up"));
		#if WITH_EDITORONLY_DATA
		Debug_PrintInventory();
		#endif
		return false;
	}

	int EmptySlotIndex;
	if(FindItemInInventory(FReducedItemStruct(), EmptySlotIndex))
	{
		UE_LOG(LogTemp,Display,TEXT("Found empty slot and overwritten it with the item"));
		Inventory[EmptySlotIndex] = Item;
		OnChangedItemSlot.Broadcast(EmptySlotIndex);
		PlayPickupSound();
		return true;
	}
	
	return false;
	
}

bool UInventoryComponent::FindItemInInventory(FReducedItemStruct Item, int& location)
{
	int index = 0;
	for(const FReducedItemStruct& item : Inventory)
	{
		if(item.ID == Item.ID)
		{
			location = index;
			return true;
		}
		index++;
	}
	return false;
}

bool UInventoryComponent::IsInventoryFull()
{
	for(const FReducedItemStruct& Item : Inventory)
	{
		if(Item.ID == 0)
		{
			return false;
		}
	}
	return true;
}

void UInventoryComponent::Debug_PrintInventory()
{
	for(FReducedItemStruct& item : Inventory)
	{
		UE_LOG(LogTemp,Display,TEXT("%s"),*item.ItemAsString());
	}
}

void UInventoryComponent::PlayPickupSound() const
{
	if(AudioComponent->IsValidLowLevel())
	{
		AudioComponent->SetSound(PickupSound);
		AudioComponent->Play();
	}
}

bool UInventoryComponent::PrepareSlotForEquip(int SlotIndex)
{
	if(!Inventory.IsValidIndex(SlotIndex))
	{
		return false;
	}

	if(ReduceItemFromSlot(SlotIndex, 1))
	{
		return true;
	}
	
	return false;
}

bool UInventoryComponent::ReduceItemFromSlot(int SlotIndex, int Amount)
{
	if(!Inventory.IsValidIndex(SlotIndex))
	{
		return false;
	}

	if(Inventory[SlotIndex].Amount - Amount < 0)
	{
		return false;
	}
	Inventory[SlotIndex].Amount -= Amount;
	if(Inventory[SlotIndex].Amount <= 0)
	{
		ClearSlot(SlotIndex);
		return true;
	}
	return true;
	
}

void UInventoryComponent::ClearSlot(int SlotIndex)
{
	if(Inventory.IsValidIndex(SlotIndex))
	{
		Inventory[SlotIndex] = FReducedItemStruct();
	}
}

bool UInventoryComponent::GetItemById(int Index, FReducedItemStruct& Item)
{
	if(!Inventory.IsValidIndex(Index))
	{
		return false;
	}
	Item = Inventory[Index];
	return true;
}

bool UInventoryComponent::EquipItem(UEquipmentComponent* EquipmentCompRef, EEquipmentType Type, FReducedItemStruct Item)
{
	if(!EquipmentComponent->IsValidLowLevel())
	{
		UE_LOG(LogTemp,Warning,TEXT("Equipment component is not valid! Cant equip item"));
		return false;
	}

	if(!EquipmentComponent->EquippedItems.IsValidIndex(static_cast<uint8>(Type)))
	{
		return false;
	}

	if(Item.ID == 0 || Item.Amount == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Cant pickup an item with amount=0 or id=0"))
		return false;
	}

	// TODO: check if the slot was empty before adding item
	// Equip the item to the slot

	if(!EquipmentComponent->IsSlotEmpty(Type))
	{
		UnequipItem(Type);
	}

	int ItemIndex;
	if(FindItemInInventory(Item,ItemIndex)) // is the item even in the inventory?
	{
		if(ItemsDatabase->GetItemByID(Item.ID).Stackable)
		{
			// if the item is stackable
			ClearSlot(ItemIndex);
		}
		else
		{
			// if the item is not stackable
			if(!ReduceItemFromSlot(ItemIndex,1)) // Subtract one item from the stack
			{
				return false;
			}
		}
		EquipmentComponent->EquipItem(Item,Type);
		return true;
	}
	
	
	
	return false;
}

/**
 * @brief Transfers an item from an equipment slot to an inventory slot
 * @param Type is the Equipmentslot where the equipment is stored in
 * @return Was the transfer successful?
 */
bool UInventoryComponent::UnequipItem(EEquipmentType Type)
{
	
	if(EquipmentComponent == nullptr)
	{
		return false;
	}

	FReducedItemStruct Item;
	if(EquipmentComponent->GetItemByType(Type,Item))
	{
		AddItemToInventory(Item);
		EquipmentComponent->EmptySlot(Type);
		return true;
	}
	return false;
}


