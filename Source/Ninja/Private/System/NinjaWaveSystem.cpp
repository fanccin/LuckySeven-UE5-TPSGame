

#include "System/NinjaWaveSystem.h"

#include "Monster/MonsterSpawner.h"

ANinjaWaveSystem::ANinjaWaveSystem()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentWave = 0;
	AllMonsterCount = 0;
	KillMonsterCount = 0;

	
}

void ANinjaWaveSystem::StartWave()
{
	if (!ensure(MonsterSpawners.Num() == WaveLevel[CurrentWave].SpawnCountPerSpawner.Num()))
	{
		UE_LOG(LogTemp,Warning,TEXT("몬스터 스포너의 수와 몬스터 스포너 데이터의 값이 일치하지 않습니다."));
		return;
	}
	for (int32 i = 0; i < MonsterSpawners.Num(); i++)
	{
		if (MonsterSpawners[i])
		{
			int32 Count = WaveLevel[CurrentWave].SpawnCountPerSpawner[i];
			MonsterSpawners[i]->SpawnMonsters(Count);
			AllMonsterCount += Count;
		}
	}
}

void ANinjaWaveSystem::OnMonsterDead() 
{
	KillMonsterCount++;
	if (KillMonsterCount == AllMonsterCount)
	{
		CurrentWave < WaveLevel.Num() - 1 ? NextWave() : OnAllWaveClear();
	}
}


void ANinjaWaveSystem::NextWave()
{
	CurrentWave++;
	KillMonsterCount = 0;
	AllMonsterCount = 0;
	StartWave();
}

void ANinjaWaveSystem::OnAllWaveClear()
{
	//TODO :: 레벨 클리어시 클리어 포탈 활성화
}
