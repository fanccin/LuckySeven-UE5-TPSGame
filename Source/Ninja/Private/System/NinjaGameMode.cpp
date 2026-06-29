// Fill out your copyright notice in the Description page of Project Settings.


#include "System/NinjaGameMode.h"

ANinjaGameMode::ANinjaGameMode() {
}

void ANinjaGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	for (const FControllerInfo& Info : ControllerTable->Controllers)
	{
		if (MapName.Contains(Info.LevelName.ToString()))
		{
			PlayerControllerClass = Info.ControllerClass;
			break;
		}
	}
}
