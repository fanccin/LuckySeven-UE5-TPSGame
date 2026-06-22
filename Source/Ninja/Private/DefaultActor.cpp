#include "DefaultActor.h"

ADefaultActor::ADefaultActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADefaultActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

