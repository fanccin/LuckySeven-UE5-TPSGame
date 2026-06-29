// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FControllerInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct NINJA_API FControllerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName LevelName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerController> ControllerClass;
};
