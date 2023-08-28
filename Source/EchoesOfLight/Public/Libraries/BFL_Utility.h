// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structures/Structs.h"
#include "Enums/Enums.h"
#include "BFL_Utility.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UBFL_Utility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
		FS_Item BPL_GetItemInfo(FDataTableRowHandle item);


	UFUNCTION(BlueprintCallable, Category = "Data Table Functions")
		FS_GameSettings BPL_GetGameSettingsInfo(FDataTableRowHandle item);
	
};
