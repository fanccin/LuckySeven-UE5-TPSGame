#include "NinjaCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "NinjaCharacterController.h"
#include "NinjaGameState.h"

//#include "NinjaCharacterControllerStage1"
//#include "NinjaCharacterStatusStage1"

// Sets default values
ANinjaCharacter::ANinjaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
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
	
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; // it's sprint is default
	
	// = Stats =	
	MaxHealth = 100.0f;
	Health = MaxHealth;
	
}

// Called when the game starts or when spawned
void ANinjaCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// === About Inputs & Control Actions ===
// Called to bind functionality to input
void ANinjaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Enhanced InputComponent로 캐스팅
    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {            	
        if (ANinjaCharacterController* PlayerController = Cast<ANinjaCharacterController>(GetController()))
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
		GetCharacterMovement()->JumpZVelocity = JumpForce;
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
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}

}
void ANinjaCharacter::StopWalk(const FInputActionValue& value)
{
	// Shift 키를 뗀 순간 이 함수가 호출
	// 평상시 속도로 복귀 (Default is Sprint)
	if (GetCharacterMovement())
	{
		SprintSpeed = WalkSpeed * SprintSpeedMultiplier;		
		
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}


// === Get Set ===

float ANinjaCharacter::GetSpeed() const
{
	return GetCharacterMovement()->MaxWalkSpeed;	

}

void ANinjaCharacter::SetSpeed(float Amount)
{
	if (GetCharacterMovement())
	{
		WalkSpeed = Amount;			
		GetCharacterMovement()->MaxWalkSpeed =  WalkSpeed * SprintSpeedMultiplier;			
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



