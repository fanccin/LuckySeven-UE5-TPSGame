// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NinjaMonster.generated.h"

class USphereComponent;

UCLASS()
class NINJA_API ANinjaMonster : public AActor
{
	GENERATED_BODY()
	
public:	
	ANinjaMonster();
	UFUNCTION(BlueprintCallable)
	float GetHp() const {return HP;}
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() const {return MaxHP;}
	UFUNCTION(BlueprintCallable)
	void SetHp(float NewHp);
	
	UFUNCTION()
	virtual void OnMonsterOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	
protected:
	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Monster")
	USceneComponent*Scene;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Monster")
	USphereComponent *DamageCollsion;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Monster")
	USphereComponent *BlockCollsion;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Monster")
	USkeletalMeshComponent* SkeletalMesh;	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float HP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float MaxHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float Damage;
	
	virtual void OnDead();
	
};
