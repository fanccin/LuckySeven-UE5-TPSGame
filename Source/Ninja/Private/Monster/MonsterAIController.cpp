#include "MonsterAIController.h"

#include "NinjaBaseMonster.h"
#include "Kismet/GameplayStatics.h"




void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ANinjaBaseMonster* Monster = Cast<ANinjaBaseMonster>(GetPawn());
	if (Monster)
	{	
		bChaseOnStart = Monster->bChaseOnStart;
		bUseRange = Monster->bUseRange;
	}
}

void AMonsterAIController::SetChaseEnabled(bool bEnable)
{
	bEnable ? bChaseOnStart ? StartChase(): DetectChase() : GetWorldTimerManager().ClearTimer(ChaseTimerHandle);
}


void AMonsterAIController::StartChase()
{

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

void AMonsterAIController::DetectChase()
{
	bUseRange? RangeDetect() : SightDetect();
}


void AMonsterAIController::RangeDetect()
{
	//TODO : 범위에 따른 탐지
}

void AMonsterAIController::SightDetect()
{
	//TODO : 시야에 따른 탐지
}
