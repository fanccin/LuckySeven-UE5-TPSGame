// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaGameInstance.h"

#include "NinjaGameState.h"

UNinjaGameInstance::UNinjaGameInstance() {
	CurrentLevelIndex = 0;
}


void UNinjaGameInstance::AddToScore(const int32 Amount) {
	ScoresByStage[CurrentLevelIndex] += Amount;
}

int32 UNinjaGameInstance::GetTotalScore()
{
	int64 TotalScore = 0;
	for (const int32 ByStage : ScoresByStage) TotalScore += ByStage;
	return TotalScore;
}