// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NinjaPlayerInputConfigDataAsset.generated.h"


UCLASS()
class NINJA_API UNinjaPlayerInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//
	
	
	//
	// Input Mapping Context
	UPROPERTY(EditAnywhere, Category="Input|Context")
	class UInputMappingContext* InputMappingContext;

	// Input Actions
	UPROPERTY(EditAnywhere, Category="Input|Actions")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input|Actions")
	class UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, Category="Input|Actions")
	class UInputAction* WalkAction;
};
