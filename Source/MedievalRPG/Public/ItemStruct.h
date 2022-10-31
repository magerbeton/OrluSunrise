// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "GearTypeEnum.h"
#include "ItemStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	//
	// Default: (Defines the basic information about every item)
	//
	// Equipment: (Holds all the necessary information to be able to equip an item to an equipment slot)
	//
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	int ItemID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FText ItemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
	FText ItemInfo;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Equipment")
	EEquipmentType EquipmentType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visuals")
	UTexture2D* ItemImg;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visuals")
	UStaticMesh* ItemMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Visuals")
	int ItemSellPrice;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Equipment")
	bool Stackable;

	// TODO: Make a function library which makes the struct functions usable by blueprints
	FString ItemAsString() const
	{
		return FString::Printf(TEXT("ItemID: %i, ItemName: %s"),ItemID,*ItemName.ToString());
	}

	FString ItemAsStringExt() const
	{
		return FString::Printf(TEXT("ID: %i, Name: %s, Description: %s, EquipmentType: %i, ItemImg: %s, StaticMesh: %s, ItemPrice: %i"),ItemID,*ItemName.ToString(),*ItemInfo.ToString(),static_cast<uint32>(EquipmentType),*ItemImg->GetPathName(),*ItemMesh->GetPathName(),ItemSellPrice);
	}
	
	FORCEINLINE FItemStruct(
		int newItemID = 0,
		FText newItemName = FText::FromString("None"),
		FText newItemInfo = FText::FromString("None"),
		EEquipmentType newEquipmentState = EEquipmentType::None,
		UTexture2D* newItemImg = nullptr,
		UStaticMesh* newItemMesh = nullptr,
		int newItemSellPrice = 0,
		bool newStackable = true
		);
	
};



UCLASS(BlueprintType)
class MEDIEVALRPG_API UItemsDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Items")
	TArray<FItemStruct> items;

	UFUNCTION(BlueprintCallable)
	void SortItems();

	UFUNCTION(BlueprintCallable)
	FItemStruct GetItemByID(int id) const;

	UItemsDatabase();
 
};

inline FItemStruct::FItemStruct(int newItemID, FText newItemName, FText newItemInfo, EEquipmentType newEquipmentState,
                                UTexture2D* newItemImg, UStaticMesh* newItemMesh, int newItemSellPrice,bool newStackable)
{
	//constructor starts here:
	ItemID = newItemID;
	ItemName = newItemName;
	ItemInfo = newItemInfo;
	EquipmentType = newEquipmentState;
	ItemImg = newItemImg;
	ItemMesh = newItemMesh;
	ItemSellPrice = newItemSellPrice;
	Stackable = newStackable;
	
}


inline void UItemsDatabase::SortItems()
{
	Algo::SortBy(items, &FItemStruct::ItemID);
}

inline FItemStruct UItemsDatabase::GetItemByID(int id) const
{
	if(items[id].ItemID == id)
	{
		return items[id];
	}
	for(const FItemStruct& item : items)
	{
		if(item.ItemID == id)
		{
			return item;
		}
	}
	return FItemStruct();
}

inline UItemsDatabase::UItemsDatabase()
{
	SortItems();
}
