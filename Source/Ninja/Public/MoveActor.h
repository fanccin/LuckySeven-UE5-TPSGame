#pragma once

class UMoveActorComponent;

#include "CoreMinimal.h"
#include "DefaultActor.h"
#include "MoveActor.generated.h"

UCLASS()
class NINJA_API AMoveActor : public ADefaultActor
{
	GENERATED_BODY()
	
public:
	AMoveActor();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move|Components")
	UMoveActorComponent* MoveComp;
};