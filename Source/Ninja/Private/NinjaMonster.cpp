// Fill out your copyright notice in the Description page of Project Settings.


#include "NinjaMonster.h"

// Sets default values
ANinjaMonster::ANinjaMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANinjaMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANinjaMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

