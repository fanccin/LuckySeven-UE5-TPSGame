#include "NinjaCharacterController.h"
#include "EnhancedInputSubsystems.h"

ANinjaCharacterController::ANinjaCharacterController()
	:InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr),
	  WalkAction(nullptr)
{	
}

void ANinjaCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				// 추후 Priority 세팅
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}