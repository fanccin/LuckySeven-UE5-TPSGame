#include "DefaultActor.h"
#include "MoveActorComponent.h"

ADefaultActor::ADefaultActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneComp);

	MoveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComp"));
}

void ADefaultActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (MoveComp)
	{
		MoveComp->asd(DeltaTime);
	}
}

