// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack = 99;

    bool IsEmpty() const
    {
        return ItemID.IsNone() || Count <= 0;
    }
};

USTRUCT(BlueprintType)
struct FItemDate
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};
class NINJA_API InventoryTypes
{
public:
	InventoryTypes();
	~InventoryTypes();

	
};
