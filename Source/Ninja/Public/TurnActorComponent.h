#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINJA_API UTurnActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTurnActorComponent();
	
	void Turn(float DeltaTime); // 회전 구현한 함수

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	float RotationSpeed = 50.f; // 회전 속도
	
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	FRotator RotationInput = FRotator(1,0,0); // 회전 축 입력
	
	AActor* Owner = nullptr; // RotationComponent를 소유하고 있는 엑터 가져올 변수
};

/*
 < .h에 입력 >
class UTurnActorComponent; 전방 선언

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	UTurnActorComponent* TurnComp;
	
 < .cpp에 입력 >
#include "UTurnActorComponent.h"

TurnComp = CreateDefaultSubobject<UTurnActorComponent>(TEXT("TurnComp")); 컴포넌트 부착
Actor컴포넌트는 SetupAttachment 사용 X

Actor의 Tick함수에 구현
if (TurnComp)
	{
		TurnComp->Turn(DeltaTime);
	}
 */