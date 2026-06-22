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
	virtual void BeginPlay() override;
	
	
};
