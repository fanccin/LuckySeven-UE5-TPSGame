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
