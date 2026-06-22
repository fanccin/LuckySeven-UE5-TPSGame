// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaGameState.h"

#include "NinjaBasePlayerController.h"
#include "NinjaGameInstance.h"


ANinjaGameState::ANinjaGameState()
{
	SpawnedMonsterCount = 0;
	KillMonsterCount = 0;
	MaxLevels = LevelMapNames.Num();
}

void ANinjaGameState::BeginPlay()
{
	Super::BeginPlay();
	
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))		ShowMainMenu();
}

void ANinjaGameState::StartLevel() {
}

int32 ANinjaGameState::GetScore() const
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GameInstance))
		{
			return NinjaGameInstance->GetTotalScore();
		}
	}
	return 0;
}

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
		NinjaGameInstance->CurrentLevelIndex = NinjaGameInstance->CurrentLevelIndex + 1;

		OnGameOver();
	}
	
}


void ANinjaGameState::OnGameOver() {
	// TODO 인구님 - 캐릭터 사망시 호출 함수
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (ANinjaBasePlayerController* SpartaPlayerController = Cast<ANinjaBasePlayerController>(PlayerController))
	{
		SpartaPlayerController->SetPause(true);
		SpartaPlayerController->ShowGameHUD(CurrentLevelScore);
	}
}

void ANinjaGameState::ShowMainMenu() {
	// TODO 신성님 - 메뉴레벨에서만 노출되는 메뉴 HUD(게임 시작, 게임 타이틀 노출 화면) 노출 필요
}
