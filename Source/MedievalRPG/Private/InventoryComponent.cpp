// All Copyright belongs to Konstantin Passig


#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	NumberOfSlots = 24;
	Inventory.Init(FReducedItemStruct(),NumberOfSlots);

	const ConstructorHelpers::FObjectFinder<UItemsDatabase>ItemDatabaseObj(TEXT("ItemsDatabase'/Game/Data/DB_Items.DB_Items'"));
	if(ItemDatabaseObj.Succeeded())
	{
		ItemsDatabase = ItemDatabaseObj.Object;
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

