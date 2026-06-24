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
	//스테이지별 최고점수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	TArray<int32> StageHighScores;
	//각 스테이지의 최고점수 합 -> 최종점수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData")
	int32 HighScoreTotal;
	//게임 클리어(4스테이지까지) 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	bool ClearedFinalStage;
	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetTotalScore();
	
};
