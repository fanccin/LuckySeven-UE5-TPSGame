#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


#include "NinjaCharacter.generated.h"

// class UWidgetComponent;

// Forward Declaration
class USpringArmComponent; // 스프링 암 관련 클래스 헤더
class UCameraComponent; // 카메라 관련 클래스 전방 선언
class UCharacterMovementComponent;

//
struct FInputActionValue; // Enhanced Input에서 액션 값을 받을 때 사용하는 구조체
struct FNinjaCharacterStatData;

UCLASS()
class NINJA_API ANinjaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	// Sets default values for this character's properties
	ANinjaCharacter();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UDataTable* CharacterStatDataTable;
	
	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UCharacterMovementComponent* MoveComp = nullptr;
	
	// === Functions ===
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void StartWalk(const FInputActionValue& value);
	UFUNCTION()
	void StopWalk(const FInputActionValue& value);
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetAirControl(float NewAirControl, float NewAirControlBoostMultiplier, float NewAirControlBoostVelocityThreshold, float NewFallingLateralFriction);
	
	
	// === Components ===
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp = nullptr;
	
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget = nullptr;
	 */
	
	// === Variables ===	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float WalkSpeed; 

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedMultiplier; 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed; // SprintSPeed = WalkSpeed * SprintSpeedMultiplier // It's default Speed	
	
	// = Jump =
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Jump")
	float JumpForce;
	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Jump")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Jump")
	float AirControl;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Jump")
	float AirControlBoostMultiplier;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Jump")
	float AirControlBoostVelocityThreshold;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Jump")
	float FallingLateralFriction;
	
	
	//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Health")
	float MaxHealth;	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat|Health")
	float Health;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stat")
	float AttackDamage;

public:		
	//virtual void Tick(float DeltaTime) override;

	//=== Get Set ===	
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetSpeed(float Amount);
	
	
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetHealth(float Amount);

	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetAttackDamage() const;
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetAttackDamage(float Amount);
	
	
	// === ===
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent, 
		AController* EventInstigator, 
		AActor* DamageCauser 
	) override;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void OnDeath();	
	
	
private:
	void Initialize();
	void InitializeCharacterStatsBasedOnDataTable();

};
