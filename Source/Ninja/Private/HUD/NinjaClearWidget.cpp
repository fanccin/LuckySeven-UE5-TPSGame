// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/NinjaClearWidget.h"
#include "System/NinjaGameInstance.h"
#include "System/NinjaGameState.h"
#include "Components/TextBlock.h"


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
	UE_LOG(LogTemp, Warning, TEXT("Widget 데이터"));
	UE_LOG(LogTemp, Warning, TEXT("Input Minutes: %d, Seconds: %d, Score: %d"), Minutes, Seconds, StageScore);
	if (!GameInstance) return;
	
	//4스테이지 클리어시 GAME CLEAR 출력
	if (GameInstance->CurrentLevelIndex == 3)
	{
		if (Text_ClearTitle) Text_ClearTitle->SetText(FText::FromString(TEXT("GAME CLEAR!")));
		GameInstance->bIsFinalStageCleared = true;
	}
	else
	{
		if (Text_ClearTitle) Text_ClearTitle->SetText(FText::FromString(TEXT("STAGE CLEAR!")));
	}
	
	bool IsNewRecord = false;
	int32 StageIndex = GameInstance->CurrentLevelIndex;
	if (GameInstance->ScoresByStage.IsValidIndex(StageIndex))
	{
		//최고점 갱신
		if (StageScore>GameInstance->ScoresByStage[StageIndex])
		{
			int32 ScoreIncrease = StageScore - GameInstance->ScoresByStage[StageIndex];
			GameInstance->AddToScore(ScoreIncrease);
			IsNewRecord = true;
		}
	}
	FString TimeStr = FString::Printf(TEXT("걸린 시간 : %02d:%02d"), Minutes, Seconds);
	FString ScoreStr = FString::Printf(TEXT("점수 : %d"), StageScore);
	FString FinalScoreStr = FString::Printf(TEXT("최종 점수 : %d"), GameInstance->GetTotalScore());
	if (Text_ClearTime)
	{
		Text_ClearTime->SetText(FText::FromString(TimeStr));
	}
	if (Text_Score)
	{
		Text_Score->SetText(FText::FromString(ScoreStr));
	}
	if (GameInstance->bIsFinalStageCleared)
	{
		if (Text_FinalScore)
		{
			Text_FinalScore->SetVisibility(ESlateVisibility::Visible);
			Text_FinalScore->SetText(FText::FromString(FinalScoreStr));
		}
		if (IsNewRecord&&Text_NewBadge)
		{
			Text_NewBadge->SetVisibility(ESlateVisibility::Visible);
		}
		else if (Text_NewBadge)
		{
			Text_NewBadge->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	

}
