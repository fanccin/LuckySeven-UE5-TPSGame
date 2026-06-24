// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaStage1PlayerController.h"
#include "NinjaGameInstance.h"
#include "NinjaClearWidget.h"
#include "NinjaGameState.h"
#include "ToolContextInterfaces.h"

ANinjaStage1PlayerController::ANinjaStage1PlayerController() {
}

void ANinjaStage1PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ANinjaStage1PlayerController::ShowGameHUD(const bool bIsNewScore)
{
	Super::ShowGameHUD(bIsNewScore);
	
	if (!ClearWidgetInstance && ClearWidgetClass)
	{
		ClearWidgetInstance = CreateWidget<UNinjaClearWidget>(this, ClearWidgetClass);
	}
	
	if (ClearWidgetInstance)
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GetGameInstance()))
		{
			int32 StageIndex = NinjaGameInstance->CurrentLevelIndex;
			int32 CurrentScore = NinjaGameInstance->ScoresByStage.IsValidIndex(StageIndex) ? NinjaGameInstance->ScoresByStage[StageIndex] : 0;
            
			int32 Minutes = 0, Seconds = 0;
			if (ANinjaGameState* GameState = GetWorld()->GetGameState<ANinjaGameState>())
			{
				float ElapsedTime = GameState->GetElapsedTime();
				Minutes = FMath::FloorToInt(ElapsedTime / 60.0f);
				Seconds = FMath::FloorToInt(ElapsedTime) % 60;
			}

			UNinjaClearWidget* ClearWidget = Cast<UNinjaClearWidget>(ClearWidgetInstance);
			if (ClearWidget)
			{
				UE_LOG(LogTemp, Warning, TEXT("=== [Controller] 전달 직전 데이터 ==="));
				UE_LOG(LogTemp, Warning, TEXT("Minutes: %d, Seconds: %d, Score: %d"), Minutes, Seconds, CurrentScore);
				ClearWidget->InitializeClearData(Minutes, Seconds, CurrentScore);
			}
			ClearWidgetInstance->AddToViewport();
			SetShowMouseCursor(true);
		}
	}	
}
//4스테이지 테스트
void ANinjaStage1PlayerController::TestClearUI()
{
	ShowGameHUD(true);
}
