#include "RotationActorComponent.h"

URotationActorComponent::URotationActorComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void URotationActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void URotationActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

