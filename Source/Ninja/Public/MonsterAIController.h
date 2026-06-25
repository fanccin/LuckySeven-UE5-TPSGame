#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

UCLASS()
class NINJA_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Monster|AI")
	void SetChaseEnabled(bool bEnable);
protected:
	
	
	FTimerHandle ChaseTimerHandle;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bChaseOnStart;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bUseRange;	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	float ChaseDelay = 1.0f;
	
	void StartChase();
	void ChasePlayer();
	void DetectChase();
	void RangeDetect();
	void SightDetect();
	
};
