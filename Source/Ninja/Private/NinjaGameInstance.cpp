// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaGameInstance.h"

UNinjaGameInstance::UNinjaGameInstance() {
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UNinjaGameInstance::AddToScore(const int32 Amount) {
	TotalScore += Amount;
}

int32 UNinjaGameInstance::GetTotalScore()
{
	return TotalScore;
}
