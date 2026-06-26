// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NinjaBaseMonster.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

class UBoxComponent;

UCLASS()
class NINJA_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonsterSpawner();
	UFUNCTION(BlueprintCallable)
	void SetMonsterChase(bool Enable);
	UFUNCTION(BlueprintCallable)
	void ReturnToPool(ANinjaBaseMonster* Monster);
	UFUNCTION(BlueprintCallable)
	void SpawnMonsters(int32 count);
	
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Monster|Spawner")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Monster|Spawner")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster|Spawner")
	FVector SpawningBoxSize;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster|Spawner")
	FVector PoolLocation;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Monster|Spawner")
	int32 PoolSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|Spawner")
	TSubclassOf<ANinjaBaseMonster> MonsterClass;
	UPROPERTY()
	TArray<ANinjaBaseMonster*> MonsterPool;
		
	FVector GetRandomPoint() const;
	ANinjaBaseMonster* SpawnMonster(TSubclassOf<AActor> MonsterClass);
	void InitPool();
	
	bool bChaseEnabel;
	
	UFUNCTION(BlueprintCallable)
	ANinjaBaseMonster* GetFromPool();
	
	virtual void BeginPlay() override;

};
