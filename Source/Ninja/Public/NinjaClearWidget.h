// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NinjaClearWidget.generated.h"

class UTextBlock;

UCLASS()
class NINJA_API UNinjaClearWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_ClearTitle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_ClearTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_FinalScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTextBlock* Text_NewBadge;

	virtual void NativeConstruct() override;
    
	UFUNCTION(BlueprintNativeEvent, Category="UI")
	void InitializeClearData(int32 Minutes, int32 Seconds, int32 StageScore);
};
