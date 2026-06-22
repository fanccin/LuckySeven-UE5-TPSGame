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

	void MoveLeftRight(float DeltaTime);
	void MoveUpDown(float DeltaTime);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float LocationSpeed = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Properties")
	float MaxRange = 0.f;
	
	virtual void BeginPlay() override;
	
private:
	AActor* Owner;
	
	FVector StartLocation;
	FVector EndLocation;
	
	float Distance = 0.f;
	
	bool LeftFirst = true;
	bool UpFirst = true;
};
