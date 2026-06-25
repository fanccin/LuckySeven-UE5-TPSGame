#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NinjaCharacterController.generated.h"

//
class UInputMappingContext;
class UInputAction; 

//
struct FInputActionValue;

UCLASS()
class NINJA_API ANinjaCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ANinjaCharacterController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	// IA	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* WalkAction;

	
protected:
	virtual void BeginPlay() override;
	
};
