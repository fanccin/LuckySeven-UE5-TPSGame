// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaBasePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "NinjaStage2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API ANinjaStage2PlayerController : public ANinjaBasePlayerController
{
	GENERATED_BODY()
	
	
public:
	ANinjaStage2PlayerController();
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	
private:
	void HandleAttack(const FInputActionValue& Value);
	void HandleInteraction(const FInputActionValue& Value);
	
};
