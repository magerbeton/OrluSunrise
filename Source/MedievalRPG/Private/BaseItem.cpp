// All Copyright belongs to Konstantin Passig


#include "BaseItem.h"

#include "InventoryComponent.h"


// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FObjectFinder<UItemsDatabase>ItemsDatabase_obj(TEXT("ItemsDatabase'/Game/Data/DB_Items.DB_Items'"));
	if(ItemsDatabase_obj.Succeeded())
	{
		AllItems = ItemsDatabase_obj.Object;
	}

	if((AllItems != nullptr) && (Item.ID != 0))
	{
		ItemMesh->SetStaticMesh(AllItems->GetItemByID(Item.ID).ItemMesh);
		ItemMesh->SetSimulatePhysics(true);
		ItemMesh->OnComponentSleep.AddDynamic(this, &ABaseItem::StopPhysicsSimulation);
	}
	
}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseItem::TryAddItemToInventory_Implementation(UInventoryComponent* Inventory)
{
	if(Inventory == nullptr)
	{
		return false;
	}
	if(Inventory->AddItemToInventory(Item))
	{
		Destroy();
		return true;
	}
	return false;
}

void ABaseItem::StopPhysicsSimulation(UPrimitiveComponent* SleepingComponent, FName BoneName)
{
	ItemMesh->SetSimulatePhysics(false);
}

