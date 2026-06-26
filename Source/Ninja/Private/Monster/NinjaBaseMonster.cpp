#include "Monster/NinjaBaseMonster.h"
#include "Monster/MonsterAIController.h"
#include "Monster/MonsterSpawner.h"
#include "Character/NinjaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ANinjaBaseMonster::ANinjaBaseMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	
	HP=MaxHP;
	Damage = 10.0f;
	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("DamageCollision"));
	DamageCollision->SetCollisionProfileName(TEXT("Trigger"));	
	DamageCollision->SetupAttachment(GetRootComponent());
	
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this,&ANinjaBaseMonster::OnMonsterOverLap);
	
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);
	
	GetCharacterMovement()->GravityScale = 0.0f;
}


void ANinjaBaseMonster::SetHp(float NewHp)
{
	HP=FMath::Clamp(NewHp,0.0f,MaxHP);
	if (HP<0.0f)
	{
		OnDead();
	}
}

void ANinjaBaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
	DamageCollision->SetCapsuleRadius(CollisionRadius);
	DamageCollision->SetCapsuleHalfHeight(CollisionHeight);

	GetCharacterMovement() -> MaxWalkSpeed = MoveSpeed;
	
}

void ANinjaBaseMonster::OnMonsterOverLap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ANinjaCharacter* Player = Cast<ANinjaCharacter>(OtherActor);
	if (Player)
	{
		UGameplayStatics::ApplyDamage(
			Player,
			Damage,
			nullptr,
			this,
			UDamageType::StaticClass()
			);
		UE_LOG(LogTemp,Warning,TEXT("OverLap"));

	}

}

void ANinjaBaseMonster::OnDead()
{
	if (OwnerSpawner)
	{
		OwnerSpawner->ReturnToPool(this);
	}
	//TODO : 몬스터 사망시 설정에 따라 수정
}

void ANinjaBaseMonster::ActivateMonster(bool bActive)
{	
	SetActorHiddenInGame(!bActive);
	SetActorEnableCollision(bActive);
	
	GetCharacterMovement()->GravityScale = bActive ? 1.0f : 0.0f;
	

}

void ANinjaBaseMonster::SetChaseEnable(bool bEnable)
{	
	AMonsterAIController* AIC = Cast<AMonsterAIController>(GetController());
	if (AIC)
	{
		AIC->SetChaseEnabled(bEnable);
	}
	
}
