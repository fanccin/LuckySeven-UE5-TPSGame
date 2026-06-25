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

UCLASS()
class NINJA_API ANinjaBasePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ClearWidgetClass;
	UPROPERTY()
	UUserWidget* ClearWidgetInstance;
	
public:
	ANinjaBasePlayerController();
	virtual void BeginPlay() override;
	
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
	
	
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameHUD(bool bIsNewScore);
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameOverHUD();
	
	//4스테이지 테스트
	UFUNCTION(Exec)
	void TestClearUI();
};
