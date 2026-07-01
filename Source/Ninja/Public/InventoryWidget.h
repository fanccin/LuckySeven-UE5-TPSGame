// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UInventoryComponent;
UCLASS()
class NINJA_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UUniformGridPanel* InventoryGrid;
	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	UInventoryComponent* InventoryRef;
};
 