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
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ClearWidgetClass;
	UPROPERTY()
	UUserWidget* ClearWidgetInstance;
public:
	ANinjaStage1PlayerController();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameHUD(bool bIsNewScore) override;
	
	//4스테이지 테스트
	UFUNCTION(Exec)
	void TestClearUI();
};
