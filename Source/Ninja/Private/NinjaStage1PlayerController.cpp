// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaStage1PlayerController.h"

#include "NinjaGameInstance.h"

ANinjaStage1PlayerController::ANinjaStage1PlayerController() {
}

void ANinjaStage1PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ANinjaStage1PlayerController::ShowGameHUD(const int32 CurrentLevelScore, const bool bIsNewScore)
{
	Super::ShowGameHUD(CurrentLevelScore, bIsNewScore);
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GameInstance))
		{
			// TODO 신성님 스테이지 종료 HUD 노출 로직 추가 필요
			// 연속으로 플레이 한 스테이지에서 얻은 총 점수 NinjaGameInstance->GetTotalScore();
			// 마지막 스테이지 클리어 여부 NinjaGameInstance->bIsFinalStageCleared
			
		}
	}
}
