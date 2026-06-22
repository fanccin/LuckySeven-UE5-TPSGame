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
		LocationSpeed *= -1;
	}
}
 
void UMoveActorComponent::Move(float DeltaTime)
{
	if (!Owner)
	{
		return;
	}
	
	FVector NewLocation;
	
	if (bMoveLeftRight)
	{
		NewLocation = FVector(LocationSpeed*DeltaTime,0.f,0.f);
	}
	else if (bMoveUpDown)
	{
		NewLocation = FVector(0.f,0.f,LocationSpeed*DeltaTime);
	}
	
	Owner->AddActorLocalOffset(NewLocation);
	EndLocation = Owner->GetActorLocation();
	Distance = FVector::Dist(StartLocation, EndLocation);
	
	if (Distance >= MaxRange)
	{
		LocationSpeed *= -1;
		StartLocation = Owner->GetActorLocation();
	}
}