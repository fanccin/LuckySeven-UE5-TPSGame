#include "Map/TurnActorComponent.h"

UTurnActorComponent::UTurnActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTurnActorComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner(); // 컴포넌트를 소유하고 있는 엑터를 Owner에 저장
}

void UTurnActorComponent::Turn(float DeltaTime)
{
	if (!Owner) // 안전 검사
	{
		return;
	}
	
	Owner->AddActorLocalRotation(RotationInput * RotationSpeed * DeltaTime);
}