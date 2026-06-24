#include "NinjaBaseMonster.h"
#include "MonsterAIController.h"
#include "NinjaCharacter.h"
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
	
	UE_LOG(LogTemp,Warning,TEXT("Base"));

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
	Destroy();
	//TODO : 몬스터 사망시 설정에 따라 수정
}
