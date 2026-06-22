// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NinjaBasePlayerController.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NINJA_API ANinjaBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameHUD(int32 CurrentLevelScore);
};
