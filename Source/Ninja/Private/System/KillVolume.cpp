// Fill out your copyright notice in the Description page of Project Settings.


#include "System/KillVolume.h"

#include "System/NinjaGameState.h"

// Sets default values
AKillVolume::AKillVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetupAttachment(Scene);
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AKillVolume::OnItemEndOverlap);
}

void AKillVolume::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		
		if (ANinjaGameState* NinjaGameState = Cast<ANinjaGameState>(GetWorld()->GetGameState()))
		{
			GEngine->AddOnScreenDebugMessage(
				-1,     // Key (-1이면 매번 새 메시지)
				5.f,    // 표시 시간
				FColor::Green,
				TEXT("플레이어 추락사!")
			);
			NinjaGameState->EndLevel();
		}
	}
}

void AKillVolume::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}
