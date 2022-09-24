// All Copyright belongs to Konstantin Passig


#include "ItemBpFuncLib.h"

FReducedItemStruct UItemBpFuncLib::ItemToReducedItem(FItemStruct Item)
{
	return FReducedItemStruct(Item.ItemID,0);
}

FReducedItemStruct UItemBpFuncLib::ItemToReducedItemCustomAmount(FItemStruct Item, int Amount)
{
	return FReducedItemStruct(Item.ItemID,Amount);
}

FString UItemBpFuncLib::ItemToString(FItemStruct Item)
{
	return Item.ItemAsString();
}

FString UItemBpFuncLib::ItemToStringExt(FItemStruct Item)
{
	return Item.ItemAsStringExt();
}

FString UItemBpFuncLib::ItemToCopyableString(FItemStruct Item)
{
	FString ReturnString = FString();
	/*ReturnString.Append("(ItemID=");
	ReturnString.Append(FString::FromInt(Item.ItemID));
	ReturnString.Append(",ItemName='");
	ReturnString.Append(Item.ItemName.ToString());
	ReturnString.Append("',ItemInfo='");
	ReturnString.Append(Item.ItemInfo.ToString());
	ReturnString.Append("',EquipmentType='");
	ReturnString.Append();
	ReturnString.Append("',ItemImg=");
	ReturnString.Append(Item.ItemImg.get);
	ReturnString.Append("");
	ReturnString.Append();*/
	return ReturnString;
}

FString UItemBpFuncLib::GetPathOfActor(UObject* Object)
{
	return Object->GetPathName();
}

FString UItemBpFuncLib::RemoveAt(FString String, int index)
{
	String.RemoveAt(index,1);
	return String;
}


