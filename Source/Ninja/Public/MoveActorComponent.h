
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
	
	void Move(float DeltaTime);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	float LocationSpeed = 100.f; // 이동 속도
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	float MaxRange = 100.f; // 이동 범위
	
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	bool bOppositeDirection = false; // 반대 방향으로 변경
	
	UPROPERTY(EditAnywhere, Category = "Item|Properties")
	FVector MoveAxis = FVector(1,0,0); // 이동 입력 축
	
	
	AActor* Owner = nullptr;
	
	FVector StartLocation;
	FVector EndLocation;
	
	float Distance = 0.f;
	
	
};

 