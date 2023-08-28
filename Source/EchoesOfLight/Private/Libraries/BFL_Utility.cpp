// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/BFL_Utility.h"

FS_Item UBFL_Utility::BPL_GetItemInfo(FDataTableRowHandle item)
{
    if (!item.DataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("DataTable is null!"));
        return FS_Item();  // Return a default item
    }

    FString Context = "BPL_GetItemInfo";
    FS_Item* ItemData = item.DataTable->FindRow<FS_Item>(item.RowName, Context);

    if (ItemData)
    {
        return *ItemData;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Item not found in DataTable!"));
        return FS_Item();  // Return a default item
    }
}


FS_GameSettings UBFL_Utility::BPL_GetGameSettingsInfo(FDataTableRowHandle item)
{
    if (!item.DataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("DataTable is null!"));
        return FS_GameSettings();  // Return a default item
    }

    FString Context = "BPL_GetItemInfo";
    FS_GameSettings* ItemData = item.DataTable->FindRow<FS_GameSettings>(item.RowName, Context);

    if (ItemData)
    {
        return *ItemData;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Item not found in DataTable!"));
        return FS_GameSettings();  // Return a default item
    }
}






