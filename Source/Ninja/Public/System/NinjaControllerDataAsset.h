// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FControllerInfo.h"
#include "Engine/DataAsset.h"
#include "NinjaControllerDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API UNinjaControllerDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TArray<FControllerInfo> Controllers;
};
