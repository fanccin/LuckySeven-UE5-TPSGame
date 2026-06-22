#include "MoveActorComponent.h"

UMoveActorComponent::UMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMoveActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UMoveActorComponent::MoveLeftRight(float DeltaTime)
{
	
}

void UMoveActorComponent::MoveUpDown(float DeltaTime)
{
	
}