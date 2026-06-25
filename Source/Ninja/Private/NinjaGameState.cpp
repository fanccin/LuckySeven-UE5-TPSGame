// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaGameState.h"

#include "NinjaBasePlayerController.h"
#include "NinjaGameInstance.h"



ANinjaGameState::ANinjaGameState()
{
	SpawnedMonsterCount = 0;
	KillMonsterCount = 0;
}

void ANinjaGameState::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	
	FString CurrentMapName = World->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))		ShowMainMenu();
	
	StartTime = World->GetTimeSeconds();
	if (UNinjaGameInstance* NinjaGameInstance = World->GetGameInstance<UNinjaGameInstance>())
	{
		for (FName LevelMapName : LevelMapNames)
		{
			NinjaGameInstance->OpenedLevels.Add(LevelMapName == "MenuLevel");
			NinjaGameInstance->ScoresByStage.Add(0);
		}
		
		LatestScore = NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex];
		NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex] = 0;
	}
	
	
}

void ANinjaGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
}

void ANinjaGameState::StartLevel() {
}

int32 ANinjaGameState::GetScore() const
{
	if (UNinjaGameInstance* NinjaGameInstance = GetGameInstance<UNinjaGameInstance>())
	{
		return NinjaGameInstance->GetTotalScore();
	}
	return 0;
}

// TODO 창훈님 - 몬스터 사망 시, 해당 함수 호출
void ANinjaGameState::AddScore(const int32 Amount) 
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GameInstance))
		{
			NinjaGameInstance->AddToScore(Amount);
		}
	}
}

void ANinjaGameState::EndLevel() {
	
	if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GetGameInstance()))
	{
		int32 CurrentIndex = NinjaGameInstance->CurrentLevelIndex;
		float LocalElapsed = GetElapsedTime();
		const float LocalMaxBonus = 1000.0f;
		const float LocalMinTime = 10.0f;
		const float LocalMaxTime = 300.0f;
		float LocalBonusScore = 0.0f;
		if (LocalElapsed<=LocalMinTime)
		{
			LocalBonusScore=LocalMaxBonus;
		}
		else if (LocalElapsed<LocalMaxTime)
		{
			float Ratio=(LocalMaxTime-LocalElapsed)/(LocalMaxTime-LocalMinTime);
			LocalBonusScore = Ratio*LocalMaxBonus;
		}
		else
		{
			LocalBonusScore = 0.0f;
		}
		int64 FinalBonusScore = FMath::FloorToInt64(LocalBonusScore);
		
		NinjaGameInstance->ScoresByStage[CurrentIndex] += FinalBonusScore;
		
		if (NinjaGameInstance->CurrentLevelIndex +1 < NinjaGameInstance->OpenedLevels.Num())
		{
			NinjaGameInstance->OpenedLevels[(NinjaGameInstance->CurrentLevelIndex)+1] = 1;
		}
		if (LevelMapNames.Num() == NinjaGameInstance->CurrentLevelIndex+1)
		{
			NinjaGameInstance->bIsFinalStageCleared = true;
		}
		OnGameOver();
	}
}


// TODO 인구님 - 캐릭터 사망시 호출 함수
void ANinjaGameState::OnGameOver() {
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (ANinjaBasePlayerController* SpartaPlayerController = Cast<ANinjaBasePlayerController>(PlayerController))
	{
		if (UNinjaGameInstance* NinjaGameInstance = World->GetGameInstance<UNinjaGameInstance>())
		{
			bool bIsNewScore = IsNewScore();
			NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex] = FMath::Max(NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex], LatestScore);
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowGameHUD(
				bIsNewScore
			);
		}
	}
}

void ANinjaGameState::ShowMainMenu() {
	// TODO 신성님 - 메뉴레벨에서만 노출되는 메뉴 HUD(게임 시작, 게임 타이틀 노출 화면) 노출 필요
}


// TODO 신성님 - 시작 경과 시간. HUD에서 해당 함수를 0.1초마다 호출
float ANinjaGameState::GetElapsedTime() const
{
	return GetWorld()->GetTimeSeconds() - StartTime;
}

bool ANinjaGameState::IsNewScore() const
{
	if (UNinjaGameInstance* NinjaGameInstance = GetWorld()->GetGameInstance<UNinjaGameInstance>())
	{
		return LatestScore < NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex];
	}
	return false;
}

