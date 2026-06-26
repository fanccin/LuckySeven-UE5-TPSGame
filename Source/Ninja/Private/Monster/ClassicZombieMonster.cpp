#include "Monster/ClassicZombieMonster.h"

AClassicZombieMonster::AClassicZombieMonster()
{
	/* 메시 직접 설정
	 *static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(
	   TEXT("메시 경로"));  
    
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	*/
	
	MoveSpeed = 100.0f;
	MaxHP = 100.0f;
	Damage = 100.0f;
	bChaseOnStart = true;
	bUseRange = false;
	CollisionRadius = 40.0f;
	CollisionHeight = 120.0f;

}

void AClassicZombieMonster::OnDead()
{
	Super::OnDead();
	//사망효과 적용 ex)일정 시간후 특정 함수 실행
}
