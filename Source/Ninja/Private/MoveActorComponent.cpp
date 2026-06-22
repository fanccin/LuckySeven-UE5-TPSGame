#include "MoveActorComponent.h"

UMoveActorComponent::UMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
	if (Owner)
	{
		StartLocation = Owner->GetActorLocation();	
	}
	
	OppositeDirection();
}

void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMoveActorComponent::OppositeDirection()
{
	if (bOppositeDirection)
	{
		MoveAxis *= -1;
	}
}
 
void UMoveActorComponent::Move(float DeltaTime)
{
	if (!Owner)
	{
		return;
	}
	
	Owner->AddActorLocalOffset(MoveAxis * LocationSpeed * DeltaTime);
	EndLocation = Owner->GetActorLocation();
	Distance = FVector::Dist(StartLocation, EndLocation);
	
	if (Distance >= MaxRange)
	{
		MoveAxis *= -1;
		StartLocation = Owner->GetActorLocation();
	}
}