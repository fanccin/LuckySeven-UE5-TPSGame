#pragma once

#include "CoreMinimal.h"
#include "NinjaBaseMonster.h"
#include "ClassicZombieMonster.generated.h"


UCLASS()
class NINJA_API AClassicZombieMonster : public ANinjaBaseMonster
{
	GENERATED_BODY()
public:
	AClassicZombieMonster();
protected:
	virtual void OnDead() override;
};
