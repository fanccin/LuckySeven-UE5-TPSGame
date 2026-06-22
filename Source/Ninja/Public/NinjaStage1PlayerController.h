// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaBasePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "NinjaStage1PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API ANinjaStage1PlayerController : public ANinjaBasePlayerController
{
	GENERATED_BODY()
	
public:
	ANinjaStage1PlayerController();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD(int32 CurrentLevelScore) override;
};
