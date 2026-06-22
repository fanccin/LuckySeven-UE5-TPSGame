#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultActor.generated.h"

class URotationActorComponent;

UCLASS()
class NINJA_API ADefaultActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADefaultActor();
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	USceneComponent* SceneComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	UStaticMeshComponent* StaticMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Components")
	URotationActorComponent* RotationComp;
	
	virtual void BeginPlay() override;
};
