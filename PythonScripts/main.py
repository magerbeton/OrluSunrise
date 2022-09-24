# Update old csv structure for items to new one
# New one::
# (ItemID=0,ItemName="None",ItemInfo="None",EquipmentType=None,ItemImg=None,ItemMesh=None,ItemSellPrice=0)
#old head:
#,ItemID,ItemName,AssembledSword/ArmorParts,Quality,ItemInfo,EquipmentID,ItemImg,StaticMesh,WeaponOrArmor,Armor/WeaponSetName,SwordPart,ArmorCustomValues,CustomWeaponsStruct,RegenHPValue,HardPrice

import pandas as pd
import csv

filename = "OldItemIds.txt"

allItems = pd.read_csv(filename)

#print(allItems)
OriginalValues = ["","ItemID","ItemName","AssembledSword/ArmorParts","Quality","ItemInfo","EquipmentID","ItemImg","StaticMesh","WeaponOrArmor","Armor/WeaponSetName","SwordPart","ArmorCustomValues","CustomWeaponsStruct","RegenHPValue","HardPrice"]
ValuesToLookFor = ['ItemID','ItemName','ItemInfo','ItemImg','StaticMesh']

EquipmentMap = {
    "Schneide": "Weapon_Blade",
    "Parierstange": "Weapon_Parry",
    "Griff": "Weapon_Grip",
    "Knauf": "Weapon_Pummel",
    "0": "Armor_Helmet",
    "1": "Armor_Chest",
    "2": "Armor_Legs",
    "3": "Weapon_Rohling",
    "4": "Armor_Foot",
    "Eddible": "Consumable"
}

def makeItemLine(row):
    ItemType = ""
    if(allItems['WeaponOrArmor'][row]=="Weapon"):
        ItemType = EquipmentMap[str(allItems['EquipmentID'][row])]
    elif(allItems['WeaponOrArmor'][row]=="WeaponPart"):
        ItemType = EquipmentMap[allItems['SwordPart'][row]]
    elif(allItems['WeaponOrArmor'][row]=="Eddible"):
        ItemType = (EquipmentMap[allItems['WeaponOrArmor'][row]])
    elif(allItems['WeaponOrArmor'][row]=="Armor"):
        ItemType = (EquipmentMap[str(allItems['EquipmentID'][row])])
        


    
    return '(ItemID='+str(allItems['ItemID'][row])+',ItemName="'+str(allItems['ItemName'][row])+'",ItemInfo="'+str(allItems['ItemInfo'][row])+'",EquipmentType='+str(ItemType)+',ItemImg='+str(allItems['ItemImg'][row])+',ItemMesh='+str(allItems['StaticMesh'][row])+',ItemSellPrice='+str(allItems['HardPrice'][row])+')'

def ClearFile():
    f = open("NewItemList.txt","w")
    f.write("")
    f.close()

ClearFile()

f = open("NewItemList.txt","a")
f.write("(")

for i in range(len(allItems['ItemID'])):
    f.write(makeItemLine(i))
    if(i+1 != len(allItems)):
        f.write(",")
    else:
        f.write(")")

f.close()    


    
    