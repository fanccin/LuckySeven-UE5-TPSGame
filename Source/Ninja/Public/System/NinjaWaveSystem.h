#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NinjaWaveSystem.generated.h"

class AMonsterSpawner;

USTRUCT(BlueprintType)
struct FWaveSpawnData
{
	GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> SpawnCountPerSpawner;
};


UCLASS()
class NINJA_API ANinjaWaveSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	ANinjaWaveSystem();
	
	UFUNCTION(BlueprintCallable)
	void StartWave();
	UFUNCTION(BlueprintCallable)
	void OnMonsterDead();
	
protected:
	
	int32 AllMonsterCount;
	int32 KillMonsterCount;
	int32 CurrentWave;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="System|Wave")
	TArray<FWaveSpawnData> WaveLevel;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="System|Wave")
	TArray<AMonsterSpawner*> MonsterSpawners;
	void OnAllWaveClear();
	void NextWave();
};
