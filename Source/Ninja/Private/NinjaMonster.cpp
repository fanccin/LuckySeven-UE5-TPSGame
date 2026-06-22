#include "NinjaMonster.h"

#include "NinjaCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ANinjaMonster::ANinjaMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	DamageCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("DamageCollision"));
	DamageCollsion->SetCollisionProfileName(TEXT("Trigger"));	
	DamageCollsion->SetupAttachment(Scene);
	
	BlockCollsion = CreateDefaultSubobject<USphereComponent>(TEXT("BlockCollision"));
	BlockCollsion->SetCollisionProfileName(TEXT("WorldDynamic"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Scene);
	
	DamageCollsion->OnComponentBeginOverlap.AddDynamic(this,&ANinjaMonster::OnMonsterOverLap);
	
	Damage = 10.0f;
}

void ANinjaMonster::SetHp(float NewHp)
{
	HP=FMath::Clamp(NewHp,0.0f,MaxHP);
	if (HP<0.0f)
	{
		OnDead();
	}
}

void ANinjaMonster::OnMonsterOverLap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
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
	}
}

void ANinjaMonster::OnDead()
{
	Destroy();
	//TODO : 몬스터 사망시 설정에 따라 수정
}

