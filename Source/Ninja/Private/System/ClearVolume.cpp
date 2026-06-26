// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ClearVolume.h"

#include "System/NinjaGameState.h"

// Sets default values
AClearVolume::AClearVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetupAttachment(Scene);
	Collision->SetSphereRadius(166.0f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	StaticMesh->SetupAttachment(Collision);
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AClearVolume::OnItemOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &AClearVolume::OnItemEndOverlap);
}

void AClearVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AClearVolume::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		
		GetWorld()->GetTimerManager().SetTimer(
			ClearTimerHandle, 
			[this]
			{
				if (ANinjaGameState* NinjaGameState = Cast<ANinjaGameState>(GetWorld()->GetGameState()))
				{
					NinjaGameState->EndLevel();
				}
			},
			0.3f, 
			false
		);
	}
}

void AClearVolume::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	
}
