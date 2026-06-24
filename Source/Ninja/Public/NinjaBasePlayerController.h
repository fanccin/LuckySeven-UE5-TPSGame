// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NinjaBasePlayerController.generated.h"

//
class UInputMappingContext;
class UInputAction; 

//
struct FInputActionValue;

UCLASS(Abstract)
class NINJA_API ANinjaBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void ShowGameHUD(bool bIsNewScore);
	
	//	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	// IA	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* WalkAction;
};
