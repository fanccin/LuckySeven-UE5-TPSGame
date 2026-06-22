#include "DefaultActor.h"
#include "RotationActorComponent.h"

ADefaultActor::ADefaultActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneComp);
	
	RotationComp = CreateDefaultSubobject<URotationActorComponent>(TEXT("Rotation"));
}

void ADefaultActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (RotationComp)
	{
		RotationComp->Rotation(DeltaTime);
	}
}

