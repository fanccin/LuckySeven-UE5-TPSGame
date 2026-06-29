// Fill out your copyright notice in the Description page of Project Settings.


#include "System/NinjaStage2PlayerController.h"

#include "EnhancedInputComponent.h"
#include "Character/NinjaCharacter.h"
#include "Character/NinjaPlayerInputConfigDataAsset.h"

#include "GameFramework/PlayerController.h" // APlayerController
#include "Engine/LocalPlayer.h" // ULocalPlayer

ANinjaStage2PlayerController::ANinjaStage2PlayerController() {
}

void ANinjaStage2PlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ANinjaStage2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInput) return;
	
	if (NinjaPlayerInputConfigDataAsset->AttackAction)
		EnhancedInput->BindAction(NinjaPlayerInputConfigDataAsset->AttackAction, ETriggerEvent::Triggered, this, &ANinjaStage2PlayerController::HandleAttack);
	if (NinjaPlayerInputConfigDataAsset->InteractionAction)
		EnhancedInput->BindAction(NinjaPlayerInputConfigDataAsset->InteractionAction, ETriggerEvent::Triggered, this, &ANinjaStage2PlayerController::HandleInteraction);
}

void ANinjaStage2PlayerController::HandleAttack(const FInputActionValue& Value)
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StartAttack(Value);
}

void ANinjaStage2PlayerController::HandleInteraction(const FInputActionValue& Value) 
{
	ANinjaCharacter* ControlledCharacter  = Cast<ANinjaCharacter>(GetPawn());
	if (!ControlledCharacter ) return;

	ControlledCharacter ->StartInteraction(Value);
}
