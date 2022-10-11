// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "ItemStruct.h"
#include "ReducedItemStruct.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

UCLASS()
class MEDIEVALRPG_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	FReducedItemStruct Item;

	UPROPERTY()
	UItemsDatabase* AllItems;
	
	UPROPERTY()
	UStaticMeshComponent* ItemMesh;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TryAddItemToInventory(UInventoryComponent* Inventory);
	virtual bool TryAddItemToInventory_Implementation(UInventoryComponent* Inventory);

	UFUNCTION()
	void StopPhysicsSimulation(UPrimitiveComponent* SleepingComponent, FName BoneName);
};
