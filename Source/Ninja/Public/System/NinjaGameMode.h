// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaControllerDataAsset.h"
#include "GameFramework/GameMode.h"
#include "NinjaGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API ANinjaGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	ANinjaGameMode();

protected:
	virtual void InitGame(
		const FString& MapName,
		const FString& Options,
		FString& ErrorMessage) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNinjaControllerDataAsset> ControllerTable;
};
