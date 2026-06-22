#include "RotationActorComponent.h"

URotationActorComponent::URotationActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URotationActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	
	OppositeDirection();
}

void URotationActorComponent::OppositeDirection()
{
	if (bOppositeDirection)
	{
		RotationInput *= -1;
	}
}

void URotationActorComponent::Rotation(float DeltaTime)
{
	if (!Owner)
	{
		return;
	}
	
	Owner->AddActorLocalRotation(RotationInput * RotationSpeed * DeltaTime);
}