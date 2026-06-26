#pragma once

#include "CoreMinimal.h"
#include "DefaultActor.h"
#include "TurnActor.generated.h"

class UTurnActorComponent;

UCLASS()
class NINJA_API ATurnActor : public ADefaultActor
{
	GENERATED_BODY()
	
public:
	ATurnActor();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turn|Components")
	UTurnActorComponent* TurnComp;
};
