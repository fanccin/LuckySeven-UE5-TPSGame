#include "Map/MoveActor.h"
#include "Map/MoveActorComponent.h"

AMoveActor::AMoveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	MoveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComp"));
}

void AMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MoveComp)
	{
		MoveComp->Move(DeltaTime);
	}
}
