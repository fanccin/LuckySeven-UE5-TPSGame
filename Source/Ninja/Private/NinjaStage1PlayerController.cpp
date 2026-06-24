// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaStage1PlayerController.h"
#include "NinjaBasePlayerController.h"

#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem, AddMappingContext
#include "EnhancedInputComponent.h" // UEnhancedInputComponent, BindAction()
#include "InputActionValue.h" // FInputActionValue

#include "GameFramework/PlayerController.h" // APlayerController
#include "Engine/LocalPlayer.h" // ULocalPlayer
#include "NinjaGameInstance.h"

ANinjaStage1PlayerController::ANinjaStage1PlayerController()
/*
		:InputMappingContext(nullptr),
		  MoveAction(nullptr),
		  JumpAction(nullptr),
		  LookAction(nullptr),
		  WalkAction(nullptr)
		  */
{
}

void ANinjaStage1PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				// 추후 Priority 세팅
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}

void ANinjaStage1PlayerController::ShowGameHUD(const bool bIsNewScore)
{
	Super::ShowGameHUD(bIsNewScore);
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UNinjaGameInstance* NinjaGameInstance = Cast<UNinjaGameInstance>(GameInstance))
		{
			// TODO 신성님 스테이지 종료 HUD 노출 로직 추가 필요
			// 스테이지 합산 점수 NinjaGameInstance->GetTotalScore();
			// 마지막 스테이지 클리어 여부 NinjaGameInstance->bIsFinalStageCleared
			// 현재 스테이지 점수 NinjaGameInstance->ScoresByStage[NinjaGameInstance->CurrentLevelIndex];
		}
	}
}
