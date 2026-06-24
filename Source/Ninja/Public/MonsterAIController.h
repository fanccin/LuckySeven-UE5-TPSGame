#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class NINJA_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bChaseOnStart;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bUseRange;	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	float ChaseDelay = 20.0f;
	
protected:
	
	
	FTimerHandle ChaseTimerHandle;

	virtual void BeginPlay() override;

	void StartChase();
	void ChasePlayer();
	void DetectChase();
	void RangeDetect();
	void SightDetect();
	
};
