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
	
	virtual void SetupInputComponent() override;
	
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UNinjaPlayerInputConfigDataAsset* NinjaPlayerInputConfigDataAsset;
	
	// 
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameHUD(bool bIsNewScore);
	UFUNCTION(BlueprintCallable, Category = "HUD")
	virtual void ShowGameOverHUD();
	
	
	//4스테이지 테스트
	UFUNCTION(Exec)
	void TestClearUI();
	
	
private:
	// Inputs
	void HandleMove(const FInputActionValue& Value);
	void HandleStartJump(const FInputActionValue& Value);
	void HandleStopJump(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	void HandleStartWalk(const FInputActionValue& Value);
	void HandleStopWalk(const FInputActionValue& Value);
};
