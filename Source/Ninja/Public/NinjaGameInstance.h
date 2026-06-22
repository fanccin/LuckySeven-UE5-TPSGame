// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NinjaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API UNinjaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNinjaGameInstance();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;
	
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetTotalScore();
	
};
