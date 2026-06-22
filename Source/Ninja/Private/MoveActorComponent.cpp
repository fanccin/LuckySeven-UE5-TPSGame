#include "MoveActorComponent.h"

UMoveActorComponent::UMoveActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMoveActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner(); // 컴포넌트를 소유하고 있는 엑터를 Owner에 저장
	if (Owner)
	{
		StartLocation = Owner->GetActorLocation();	// 엑터가 저장됐다면 해당 엑터의 위치 가져옴
	}
	
	OppositeDirection(); // 방향 반대로 할지 체크는 처음 1회만
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
	if (!Owner) // 안전검사
	{
		return;
	}
	
	Owner->AddActorLocalOffset(MoveAxis * LocationSpeed * DeltaTime);
	EndLocation = Owner->GetActorLocation();
	Distance = FVector::Dist(StartLocation, EndLocation);
	
	if (Distance >= MaxRange) // 이동거리가 최대 이동 범위에 도달하면
	{
		MoveAxis *= -1; // 방향 반대로
		StartLocation = Owner->GetActorLocation();
	}
}