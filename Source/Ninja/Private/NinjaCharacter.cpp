#include "NinjaCharacter.h"

#include "EnhancedInputComponent.h"
#include "NinjaBasePlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "NinjaCharacterController.h"
#include "NinjaCharacterStatData.h"
#include "NinjaGameState.h"

//#include "NinjaCharacterControllerStage1"
//#include "NinjaCharacterStatusStage1"


// Sets default values
ANinjaCharacter::ANinjaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Initialize();	
	
}
void ANinjaCharacter::Initialize()
{
	MoveComp = GetCharacterMovement();
	
	Tags.Add(FName("Player"));
	
	// === Setup ===
	// = Components =
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f; // it's temp value
	SpringArmComp->bUsePawnControlRotation = true;  
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
	
	//bUseControllerRotationYaw = true;
	
	// = Basic Character Movement =
	WalkSpeed = 500.0f; // temp value
	SprintSpeedMultiplier = 2.0f; // temp value
	SprintSpeed = WalkSpeed * SprintSpeedMultiplier;
	
	MoveComp->MaxWalkSpeed = SprintSpeed; // it's sprint is default
	
	// = Stats =	
	MaxHealth = 100.0f;
	Health = MaxHealth;
	
	// = Jump
	JumpForce = 600.0f;
	MoveComp->JumpZVelocity = JumpForce;
	
	// 공중 제어력 설정 (0.0 ~ 1.0 사이, 1.0은 지상과 동일한 제어력)
	AirControl = 1.0f;
	MoveComp->AirControl = AirControl;
	
	// 공중 제어 부스트 배율 설정 (점프 키 유지 시 제어력 증폭)
	AirControlBoostMultiplier = 2.0f;
	MoveComp->AirControlBoostMultiplier = AirControlBoostMultiplier;
	
	// 공중 제어 부스트가 발동할 속도 임계값
	AirControlBoostVelocityThreshold = 25.0f;
	MoveComp->AirControlBoostVelocityThreshold = AirControlBoostVelocityThreshold;
	
	// 공중 가로 마찰력 (값이 높을수록 공중에서 입력 중지 시 즉시 멈춤)
	FallingLateralFriction = 0.5f;
	MoveComp->FallingLateralFriction = FallingLateralFriction;
}


void ANinjaCharacter::InitializeCharacterStatsBasedOnDataTable()
{
	// CharacterStatDataTable->FindRow<>()	
	// 어차피 스테이지에서 한번씩만 가져오는거라 FindRow 면 충분할텐데 일단 혹시모르니 다 가져오는걸로
	// 추후 변경	
	TArray<FNinjaCharacterStatData*> CharacterStatDataArray;
	static const FString ContenxtString(TEXT("CharacterContext"));
	CharacterStatDataTable->GetAllRows<FNinjaCharacterStatData>(ContenxtString, CharacterStatDataArray);
	
	if (CharacterStatDataArray.IsEmpty())
		return;
	
	for (FNinjaCharacterStatData* Data : CharacterStatDataArray)
	{
		// 여기서 현재 Stage스테이지나 캐릭터에 따라서 확인 후 설정			
		//Data->StageIndex
		WalkSpeed = Data->WalkSpeed;
		SprintSpeedMultiplier = Data->SprintSpeedMultiplier;
		SprintSpeed = WalkSpeed * SprintSpeedMultiplier;
		MoveComp->MaxWalkSpeed = SprintSpeed;
			
		JumpForce = Data->JumpForce;
		MoveComp->JumpZVelocity = JumpForce;
			
		AirControl = Data->AirControl;
		MoveComp->AirControl = AirControl;
			
		AirControlBoostMultiplier = Data->AirControlBoostMultiplier;
		MoveComp->AirControlBoostMultiplier = AirControlBoostMultiplier;
			
		AirControlBoostVelocityThreshold = Data->AirControlBoostVelocityThreshold;
		FallingLateralFriction = Data->FallingLateralFriction;
			
		MaxHealth = Data->MaxHealth;
		Health = Data->Health;
			
		AttackDamage = Data->AttackDamage;
	}
	
}

// Called when the game starts or when spawned
void ANinjaCharacter::BeginPlay()
{
	Super::BeginPlay();	
	
	if (CharacterStatDataTable)
		InitializeCharacterStatsBasedOnDataTable();	
	
	
}

// === About Inputs & Control Actions ===
// Called to bind functionality to input
void ANinjaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!EnhancedInput) 
		return;	
	
	if (ANinjaBasePlayerController* PlayerController = Cast<ANinjaBasePlayerController>(GetController()))
	{
        	// null check
            if (PlayerController->MoveAction)
            {
                // IA_Move 액션 키를 "키를 누르고 있는 동안" Move() 호출
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ANinjaCharacter::Move
                );
            }
            
            if (PlayerController->JumpAction)
            {
                // IA_Jump 액션 키를 "키를 누르고 있는 동안" StartJump() 호출
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ANinjaCharacter::StartJump
                );
                
                // IA_Jump 액션 키에서 "손을 뗀 순간" StopJump() 호출
                EnhancedInput->BindAction(
                    PlayerController->JumpAction,
                    ETriggerEvent::Completed,
                    this,
                    &ANinjaCharacter::StopJump
                );
            }        	
            
            if (PlayerController->LookAction)
            {
                // IA_Look 액션 마우스가 "움직일 때" Look() 호출
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &ANinjaCharacter::Look
                );
            }
            
            if (PlayerController->WalkAction)
            {
                // IA_Walk 액션 키를 "누르고 있는 동안" StartWalk() 호출
                EnhancedInput->BindAction(
                    PlayerController->WalkAction,
                    ETriggerEvent::Triggered,                   
                    this, 
                    &ANinjaCharacter::StartWalk
                );
                // IA_Walk 액션 키에서 "손을 뗀 순간" StopWlak() 호출
                EnhancedInput->BindAction(
                    PlayerController->WalkAction, 
                    ETriggerEvent::Completed, 
                    this, 
                    &ANinjaCharacter::StopWalk
                );
            }    
        }
	
}


void ANinjaCharacter::SetAirControl(float NewAirControl, float NewAirControlBoostMultiplier, float NewAirControlBoostVelocityThreshold, float NewFallingLateralFriction )
{
	if (MoveComp)
	{	
		AirControl = NewAirControl;
		MoveComp->AirControl = AirControl;
		
		AirControlBoostMultiplier = NewAirControlBoostMultiplier;
		MoveComp->AirControlBoostMultiplier = AirControlBoostMultiplier;
		
		AirControlBoostVelocityThreshold = NewAirControlBoostVelocityThreshold;
		MoveComp->AirControlBoostVelocityThreshold = AirControlBoostVelocityThreshold;
		
		FallingLateralFriction = NewFallingLateralFriction;
		MoveComp->FallingLateralFriction = FallingLateralFriction ;
	}
}


void ANinjaCharacter::Move(const FInputActionValue& value)
{
	
	if (!Controller) return;
	
	const FVector2D MoveInput = value.Get<FVector2D>();	
	
	if (!FMath::IsNearlyZero(MoveInput.X))
	{				
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void ANinjaCharacter::Look(const FInputActionValue& value)
{	
	FVector2D LookInput = value.Get<FVector2D>();
	
	AddControllerYawInput(LookInput.X);
	
	AddControllerPitchInput(LookInput.Y);
}

void ANinjaCharacter::StartJump(const FInputActionValue& value)
{	
	if (value.Get<bool>())
	{
		// 혹시라도 인게임중 점프 높이 변경이 없을 시 빼면 됩니다.
		MoveComp->JumpZVelocity = JumpForce;
		
		Jump();
	}
}
void ANinjaCharacter::StopJump(const FInputActionValue& value)
{	
	if (!value.Get<bool>())
	{
		StopJumping();
	}	
}

void ANinjaCharacter::StartWalk(const FInputActionValue& value)
{
	// Shift 키를 누른 순간 이 함수가 호출된다고 가정
	// WalkSpeed 를 적용
	if (MoveComp)
	{
		MoveComp->MaxWalkSpeed = WalkSpeed;
	}

}
void ANinjaCharacter::StopWalk(const FInputActionValue& value)
{
	// Shift 키를 뗀 순간 이 함수가 호출
	// 평상시 속도로 복귀 (Default is Sprint)
	if (MoveComp)
	{
		SprintSpeed = WalkSpeed * SprintSpeedMultiplier;		
		
		MoveComp->MaxWalkSpeed = SprintSpeed;
	}
}


// === Get Set ===

float ANinjaCharacter::GetSpeed() const
{
	if (MoveComp)
	{
		return MoveComp->MaxWalkSpeed;
	}
	return WalkSpeed;	

}

void ANinjaCharacter::SetSpeed(float Amount)
{
	if (MoveComp)
	{
		WalkSpeed = Amount;			
		MoveComp->MaxWalkSpeed =  WalkSpeed * SprintSpeedMultiplier;			
	}
}


float ANinjaCharacter::GetHealth() const
{
	return Health;
}


void ANinjaCharacter::SetHealth(float Amount)
{
	// set clamp for min max health
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	
}

float ANinjaCharacter::GetAttackDamage() const
{
	return AttackDamage;
}

void ANinjaCharacter::SetAttackDamage(float Amount)
{
	AttackDamage = Amount;
}
// === ===


// === ===
float ANinjaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 기본 데미지 처리 로직 호출 (필수는 아님)
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 체력을 데미지만큼 감소시키고, 0 이하로 떨어지지 않도록 Clamp
	//Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	SetHealth(-ActualDamage);

	// 체력이 0 or 이하가 되면 사망 처리
	if (Health <= 0.0f)
	{
		OnDeath();
	}

	// 실제 적용된 데미지를 반환
	return ActualDamage;
}

void ANinjaCharacter::OnDeath()
{	
	if (!GetWorld()) return;


	if (ANinjaGameState* NinjaGameState = GetWorld()->GetGameState<ANinjaGameState>())
	{
		NinjaGameState->OnGameOver();
	}
	
	
}



