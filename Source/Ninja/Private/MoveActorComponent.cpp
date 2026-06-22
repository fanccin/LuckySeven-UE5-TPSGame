#include "MoveActorComponent.h"

UMoveActorComponent::UMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	StartLocation = Owner->GetActorLocation();
}

void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (LeftFirst)
	{
		MoveLeftRight(DeltaTime);
	}
	if (UpFirst)
	{
		MoveUpDown(DeltaTime);
	}
}

void UMoveActorComponent::MoveLeftRight(float DeltaTime)
{
	if (Owner)
	{
		Owner->AddActorLocalOffset(FVector(LocationSpeed*DeltaTime,0.f,0.f));
		EndLocation = Owner->GetActorLocation();
		Distance = FVector::Dist(StartLocation, EndLocation);
	}
}

void UMoveActorComponent::MoveUpDown(float DeltaTime)
{
	if (Owner)
	{
		Owner->AddActorLocalOffset(FVector(0.f,0.f,LocationSpeed*DeltaTime));
		EndLocation = Owner->GetActorLocation();
		Distance = FVector::Dist(StartLocation, EndLocation);
	}
}