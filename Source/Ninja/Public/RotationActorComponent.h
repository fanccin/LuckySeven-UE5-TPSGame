#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotationActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NINJA_API URotationActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URotationActorComponent();
	
	void Rotation(float DeltaTime); // 회전 구현한 함수

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
class URotationActorComponent; 전방 선언

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	URotationActorComponent* RotationComp;
	
 < .cpp에 입력 >
#include "RotationActorComponent.h"

RotationComp = CreateDefaultSubobject<URotationActorComponent>(TEXT("Rotation")); 컴포넌트 부착
Actor컴포넌트는 SetupAttachment 사용 X

Actor의 Tick함수에 구현
if (RotationComp)
	{
		RotationComp->Rotation(DeltaTime);
	}
 */
