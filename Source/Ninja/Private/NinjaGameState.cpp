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
	
	StartTime = GetWorld()->GetTimeSeconds();
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle, 
		[this]
		{
			
			GEngine->AddOnScreenDebugMessage(
				-1,     // Key (-1이면 매번 새 메시지)
				0.1f,    // 표시 시간
				FColor::Green,
				FString::Printf(TEXT("Time : %.1f"), GetElapsedTime())
			);
		},
		0.1f, 
		true
	);
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
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GameInstance))
		{
			return NinjaGameInstance->GetTotalScore();
		}
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


// TODO 신성님 - 시작 경과 시간. HUD에서 해당 함수를 0.1초마다 호출
float ANinjaGameState::GetElapsedTime() const
{
	return GetWorld()->GetTimeSeconds() - StartTime;
}