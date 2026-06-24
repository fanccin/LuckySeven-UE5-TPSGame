// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaClearWidget.h"
#include "Components/TextBlock.h"
#include "NinjaGameInstance.h"
#include "NinjaGameState.h"


void UNinjaClearWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Text_ClearTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ClearTitle_Design")));
	Text_ClearTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ClearTime_Design")));
	Text_Score = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Score_Design")));
	Text_FinalScore = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_FinalScore_Design")));
	Text_NewBadge = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_NewBadge_Design")));
	//최종점수와 New표시는 숨김
	if (Text_FinalScore) Text_FinalScore->SetVisibility(ESlateVisibility::Collapsed);
	if (Text_NewBadge) Text_NewBadge->SetVisibility(ESlateVisibility::Collapsed);
	
}

void UNinjaClearWidget::InitializeClearData_Implementation(int32 Minutes, int32 Seconds,int32 StageScore)
{
	UNinjaGameInstance* GameInstance = Cast<UNinjaGameInstance>(GetGameInstance());
	if (!GameInstance) return;
	
	//4스테이지 클리어시 GAME CLEAR 출력
	if (GameInstance->CurrentLevelIndex == 3)
	{
		if (Text_ClearTitle) Text_ClearTitle->SetText(FText::FromString(TEXT("GAME CLEAR!")));
		GameInstance->ClearedFinalStage = true;
	}
	else
	{
		if (Text_ClearTitle) Text_ClearTitle->SetText(FText::FromString(TEXT("STAGE CLEAR!")));
	}
	
	bool IsNewRecord = false;
	int32 StageIndex = GameInstance->CurrentLevelIndex;
	if (GameInstance->StageHighScores.IsValidIndex(StageIndex))
	{
		//최고점 갱신
		if (StageScore>GameInstance->StageHighScores[StageIndex])
		{
			int32 ScoreIncrease = StageScore - GameInstance->StageHighScores[StageIndex];
			GameInstance->StageHighScores[StageIndex] = StageScore;
			GameInstance->HighScoreTotal += ScoreIncrease;
			IsNewRecord = true;
		}
	}
	
	//점수갱신시 New 표시
	if (GameInstance->ClearedFinalStage)
	{
		if (Text_FinalScore) Text_FinalScore->SetVisibility(ESlateVisibility::Visible);
		if (IsNewRecord&&Text_NewBadge)
		{
			Text_NewBadge->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	ANinjaGameState* GameState = Cast<ANinjaGameState>(GetWorld()->GetGameState());
        if (!GameState) return;
            
        float TotalSeconds = GameState->GetElapsedTime();
        Minutes = FMath::FloorToInt(TotalSeconds / 60.0f);
        Seconds = FMath::FloorToInt(TotalSeconds) % 60;
}
