#include "TurnActor.h"
#include "TurnActorComponent.h"

ATurnActor::ATurnActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TurnComp = CreateDefaultSubobject<UTurnActorComponent>(TEXT("TurnComp"));
}

void ATurnActor::Tick(float DeltaTime)
{
	if (TurnComp)
	{
		TurnComp->Turn(DeltaTime);
	}
}