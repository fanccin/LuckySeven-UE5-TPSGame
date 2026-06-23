#include "MonsterAIController.h"

#include "Kismet/GameplayStatics.h"

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
	bChaseOnStart? StartChase() : DetectChase();
	UE_LOG(LogTemp,Warning,TEXT("StartChase"));

}

void AMonsterAIController::DetectChase()
{
	bUseRange? RangeDetect() : SightDetect();
}

void AMonsterAIController::StartChase()
{
	UE_LOG(LogTemp,Warning,TEXT("StartChase2"));

	GetWorldTimerManager().SetTimer(
		ChaseTimerHandle,
		this,
		&AMonsterAIController::ChasePlayer,
		0.1f,
		true,
		ChaseDelay);
}

void AMonsterAIController::ChasePlayer()
{
	UE_LOG(LogTemp,Warning,TEXT("StartChase3"));

	APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (Player)
	{	
		MoveToActor(Player);
		FVector PawnVel = GetPawn()->GetVelocity().GetSafeNormal();
		if (!PawnVel.IsNearlyZero())
		{
			FRotator NewRotation = FRotationMatrix::MakeFromX(PawnVel).Rotator();
			SetControlRotation(NewRotation);
		}
	}
}


void AMonsterAIController::RangeDetect()
{
	//TODO : 범위에 따른 탐지
}

void AMonsterAIController::SightDetect()
{
	//TODO : 시야에 따른 탐지
}
