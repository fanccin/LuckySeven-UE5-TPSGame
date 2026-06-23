// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "NinjaGameState.generated.h"

/**
 * 
 */
UCLASS()
class NINJA_API ANinjaGameState : public AGameState
{
	GENERATED_BODY()

	
public:
	ANinjaGameState();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	int32 SpawnedMonsterCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster")
	int32 KillMonsterCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapNames;
	UPROPERTY(BlueprintReadOnly)
	float StartTime;
	int32 LatestScore;
	
	FTimerHandle TimerHandle;
	
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu();
	UFUNCTION(BlueprintPure)
	float GetElapsedTime() const;
	
	void StartLevel();
	void EndLevel();
	bool IsNewScore() const;
};
