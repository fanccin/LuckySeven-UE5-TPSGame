#include "DefaultActor.h"

ADefaultActor::ADefaultActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneComp);
}

void ADefaultActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

