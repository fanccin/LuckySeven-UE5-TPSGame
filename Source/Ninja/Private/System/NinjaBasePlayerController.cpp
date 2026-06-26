// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaBasePlayerController.h"

#include "EnhancedInputSubsystems.h" // UEnhancedInputLocalPlayerSubsystem, AddMappingContext
#include "EnhancedInputComponent.h" // UEnhancedInputComponent, BindAction()

#include "NinjaPlayerInputConfigDataAsset.h"

#include "NinjaCharacter.h"

#include "NinjaClearWidget.h"
#include "NinjaGameInstance.h"

#include "NinjaGameState.h"


ANinjaBasePlayerController::ANinjaBasePlayerController() 
{
}

void ANinjaBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			
			if (NinjaPlayerInputConfigDataAsset && NinjaPlayerInputConfigDataAsset->InputMappingContext)
			{
				Subsystem->AddMappingContext(NinjaPlayerInputConfigDataAsset->InputMappingContext, 0);
			}

		}
	}
}

void ANinjaBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
		
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInput) return;
	
	if (!NinjaPlayerInputConfigDataAsset) return;
	

	if (NinjaPlayerInputConfigDataAsset->MoveAction)
		EnhancedInput->BindAction(NinjaPlayerInputConfigDataAsset->MoveAction, ETriggerEvent::Triggered, this, &ANinjaBasePlayerController::HandleMove		);
	if (NinjaPlayerInputConfigDataAsset->LookAction)
		EnhancedInput->BindAction(NinjaPlayerInputConfigDataAsset->LookAction, ETriggerEvent::Triggered, this, &ANinjaBasePlayerController::HandleLook);
	if (NinjaPlayerInputConfigDataAsset->JumpAction)
	{
		EnhancedInput->BindAction(
			NinjaPlayerInputConfigDataAsset->JumpAction, 
			ETriggerEvent::Triggered,
			this,
			&ANinjaBasePlayerController::HandleStartJump	
		);                
		
		EnhancedInput->BindAction(
			NinjaPlayerInputConfigDataAsset->JumpAction, 
			ETriggerEvent::Completed,
			this,
			&ANinjaBasePlayerController::HandleStopJump	
		);
	}		
	if (NinjaPlayerInputConfigDataAsset->WalkAction)
	{		
		EnhancedInput->BindAction(
			NinjaPlayerInputConfigDataAsset->WalkAction,
			ETriggerEvent::Triggered,                   
			this, 
			&ANinjaBasePlayerController::HandleStartWalk
		);
		
		EnhancedInput->BindAction(
			NinjaPlayerInputConfigDataAsset->WalkAction, 
			ETriggerEvent::Completed, 
			this, 
			&ANinjaBasePlayerController::HandleStopWalk
		);
	}
	
	
}

void ANinjaBasePlayerController::HandleMove(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->Move(Value);
}

void ANinjaBasePlayerController::HandleStartJump(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StartJump(Value);
}

void ANinjaBasePlayerController::HandleStopJump(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StopJump(Value);
}

void ANinjaBasePlayerController::HandleLook(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->Look(Value);
}

void ANinjaBasePlayerController::HandleStartWalk(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StartWalk(Value);
}

void ANinjaBasePlayerController::HandleStopWalk(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StopWalk(Value);
}


void ANinjaBasePlayerController::TestClearUI() {
}

void ANinjaBasePlayerController::ShowGameHUD(const bool bIsNewScore)
{
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

void ANinjaBasePlayerController::ShowGameOverHUD() {
}
