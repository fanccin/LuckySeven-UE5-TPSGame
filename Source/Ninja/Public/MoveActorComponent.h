
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveActorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINJA_API UMoveActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoveActorComponent();
	
	void OppositeDirection(); // 이동 방향 반대로 바꾸는 함수
	void Move(float DeltaTime); // 움직임 구현한 함수
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	float LocationSpeed = 100.f; // 이동 속도
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	float MaxRange = 100.f; // 최대 이동 범위
	
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	bool bOppositeDirection = false; // 반대 방향으로 변경
	
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	FVector MoveAxis = FVector(1,0,0); // 이동 입력 축(방향)
	
	
	AActor* Owner = nullptr; // MoveComponent를 소유하고 있는 엑터 가져올 변수
	
	FVector StartLocation;
	FVector EndLocation;
	
	float Distance = 0.f;
};

/*
 < .h에 입력 >
class UMoveActorComponent; 전방 선언

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	UMoveActorComponent* MoveComp;
	
 < .cpp에 입력 >
#include "MoveActorComponent.h"

MoveComp = CreateDefaultSubobject<UMoveActorComponent>(TEXT("MoveComp")); 컴포넌트 부착
Actor컴포넌트는 SetupAttachment 사용 X

Actor의 Tick함수에 구현
if (MoveComp)
	{
		MoveComp->Move(DeltaTime);
	}
 */

 