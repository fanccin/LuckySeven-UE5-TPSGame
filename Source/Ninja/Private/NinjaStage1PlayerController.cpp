// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaStage1PlayerController.h"
#include "NinjaBasePlayerController.h"

#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem, AddMappingContext
#include "EnhancedInputComponent.h" // UEnhancedInputComponent, BindAction()
#include "InputActionValue.h" // FInputActionValue
#include "NinjaClearWidget.h"
#include "GameFramework/PlayerController.h" // APlayerController
#include "Engine/LocalPlayer.h" // ULocalPlayer
#include "NinjaGameInstance.h"
#include "NinjaGameState.h"

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
			else
			{
				UE_LOG(LogTemp, Error, TEXT("controller 에러 : GameState = NULL"));
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
