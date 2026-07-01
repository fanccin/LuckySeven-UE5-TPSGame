// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/InventoryTypes.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class NINJA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RowCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ColumnCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInventorySlot> Slots;

	UFUNCTION(BlueprintCallable)
	bool AddItem(FName ItemID, int32 Count);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(int32 SlotIndex, int32 Count);

	UFUNCTION(BlueprintCallable)
	bool MoveItem(int32 FromIndex, int32 ToIndex);

	UFUNCTION(BlueprintCallable)
	FInventorySlot GetSlot(int32 SlotIndex) const;

	UFUNCTION(BlueprintCallable)
	bool IsValidSlotIndex(int32 SlotIndex) const;
	
	UFUNCTION(BlueprintCallable)
	void SortItem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
