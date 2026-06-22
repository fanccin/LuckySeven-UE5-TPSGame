#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultActor.generated.h"

UCLASS()
class NINJA_API ADefaultActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefaultActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
