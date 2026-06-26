#pragma once

#include "CoreMinimal.h"
#include "NinjaCharacterStatData.generated.h"

USTRUCT(BlueprintType)
struct  FNinjaCharacterStatData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stage")
	int32 StageIndex;		
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float WalkSpeed;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float SprintSpeedMultiplier;
	
	// = Jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float JumpForce;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float AirControl;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float AirControlBoostMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float AirControlBoostVelocityThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Movement")
	float FallingLateralFriction;
	 
	
	// 	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Health")
	float MaxHealth;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat/Health")
	float Health;
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float AttackDamage;
	
};
