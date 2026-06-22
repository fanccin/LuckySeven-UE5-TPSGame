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

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
