#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NinjaBaseMonster.generated.h"

class AMonsterSpawner;
class USphereComponent;

UCLASS()
class NINJA_API ANinjaBaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	ANinjaBaseMonster();
	UFUNCTION(BlueprintCallable)
	float GetHp() const {return HP;}
	UFUNCTION(BlueprintCallable)
	float GetMaxHp() const {return MaxHP;}
	UFUNCTION(BlueprintCallable)
	void SetHp(float NewHp);
	UFUNCTION(BlueprintCallable)
	void ActivateMonster(bool bActive);
	UFUNCTION(BlueprintCallable)
	void SetChaseEnable(bool bEnable);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bChaseOnStart = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|AI")
	bool bUseRange = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster|Spawner")
	AMonsterSpawner* OwnerSpawner  =nullptr;

	virtual void BeginPlay() override;

protected:

	UFUNCTION()
	virtual void OnMonsterOverLap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	UCapsuleComponent *DamageCollision;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float HP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float MaxHP;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Monster")
	float MoveSpeed;
	float CollisionRadius;
	float CollisionHeight;
	
	virtual void OnDead();
};
