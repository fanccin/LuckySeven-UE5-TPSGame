#include "Monster/MonsterSpawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AMonsterSpawner::AMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); 
	SetRootComponent(Scene);
	
	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
	
	PoolLocation = FVector(0.0f,0.0f,5000.0f);

}

void AMonsterSpawner::SetMonsterChase(bool Enable)
{
	bChaseEnabel= Enable;
	
	for (auto* Monster : MonsterPool)
	{
		if (Monster && !Monster->IsHidden())
		{
			Monster->SetChaseEnable(Enable);
		}
	}
}

FVector AMonsterSpawner::GetRandomPoint() const
{
	FVector Center = SpawningBox->GetComponentLocation();
	FVector Extent = SpawningBox->GetScaledBoxExtent();
	
	FBox SpanwBox = FBox(Center - Extent,Center+Extent);
	FVector RandPoint = FMath::RandPointInBox(SpanwBox);
	return RandPoint;
}

ANinjaBaseMonster* AMonsterSpawner::SpawnMonster(TSubclassOf<AActor> InMonsterClass)
{
	FTransform PoolTransForm(FRotator::ZeroRotator,PoolLocation);
	FActorSpawnParameters PoolParameter;
	PoolParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ANinjaBaseMonster* Monster = GetWorld()->SpawnActor<ANinjaBaseMonster>(InMonsterClass,PoolTransForm,PoolParameter);
	return Monster;
}

void AMonsterSpawner::InitPool()
{
	for (int32 i = 0; i < PoolSize;i++)
	{
		ANinjaBaseMonster* Monster = SpawnMonster(MonsterClass);
		if (Monster)
		{
			MonsterPool.Add(Monster);
		}
	}
}

ANinjaBaseMonster* AMonsterSpawner::GetFromPool()
{    UE_LOG(LogTemp, Warning, TEXT("Pool Size: %d"), MonsterPool.Num());

	for (auto Monster : MonsterPool)
	{
		UE_LOG(LogTemp, Warning, TEXT("Monster Hidden: %d"), Monster->IsHidden());

		if (Monster && Monster->IsHidden())
		{APawn* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
			if (Player)
			{
				FVector Direction = Player->GetActorLocation() - Monster->GetActorLocation();
				Direction.Z = 0.0f;
				FRotator LookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
				Monster->SetActorLocationAndRotation(GetRandomPoint(),LookAt);
				Monster->ActivateMonster(true);
				Monster->SetChaseEnable(bChaseEnabel);
				Monster->OwnerSpawner = this;
				
				return Monster;
			}
		}
	}
	return nullptr;
}

void AMonsterSpawner::ReturnToPool(ANinjaBaseMonster* Monster)
{
	if (Monster)
	{
		Monster->ActivateMonster(false);
		Monster->SetActorLocation(PoolLocation);
	}
	
}

void AMonsterSpawner::SpawnMonsters(int32 count)
{
	for (int32 i = 0;i<count;i++)
	{
		GetFromPool();
	}
}


void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();	
	UE_LOG(LogTemp,Warning,TEXT("Start"));
	SpawningBox->SetBoxExtent(SpawningBoxSize);
	InitPool();
}
