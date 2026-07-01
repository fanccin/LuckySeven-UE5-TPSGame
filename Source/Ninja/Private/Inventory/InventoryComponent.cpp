// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	const int32 SlotCount = RowCount * ColumnCount;
	Slots.SetNum(SlotCount);
	// ...
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Count)
{
	if (ItemID.IsNone() || Count <= 0)
	{
		return false;
	}
	
	//같은 아이템이 존재?
	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.ItemID == ItemID && Slot.Count < Slot.MaxStack)
		{
			const int32 AddCount = FMath::Min(Count, Slot.MaxStack - Slot.Count);
			Slot.Count += AddCount;
			Count -= AddCount;
			
			if (Count <= 0)
				return true;
		}
	}
	
	//빈 슬롯 찾기
	for (FInventorySlot& Slot : Slots)
	{
		if (Slot.IsEmpty())
		{
			Slot.ItemID = ItemID;
			Slot.Count = Count;
			
			return true;
		}
	}
	
	return false;
}

bool UInventoryComponent::RemoveItem(int32 SlotIndex, int32 Count)
{
	if (!IsValidSlotIndex(SlotIndex))
		return false;
	if (Count <= 0)
		return false;
	FInventorySlot& Slot = Slots[SlotIndex];
	
	if (Slot.IsEmpty())
		return false;
	if (Slot.Count < Count)
		return false;
	
	Slot.Count -= Count;

	if (Slot.Count <= 0)
	{
		Slot.ItemID = NAME_None;
		Slot.Count = 0;
	}
	return true;
}

bool UInventoryComponent::MoveItem(int32 FromIndex, int32 ToIndex)
{
	if (!Slots.IsValidIndex(FromIndex) || !Slots.IsValidIndex(ToIndex))
	{
		return false;
	}
	Slots.Swap(FromIndex, ToIndex);
	return true;
}

FInventorySlot UInventoryComponent::GetSlot(int32 SlotIndex) const
{
	if (IsValidSlotIndex(SlotIndex))
		return Slots[SlotIndex];
	
	return Slots[0];
}

bool UInventoryComponent::IsValidSlotIndex(int32 SlotIndex) const
{
	return Slots.IsValidIndex(SlotIndex);
}

void UInventoryComponent::SortItem()
{
	Slots.Sort([](const FInventorySlot& A, const FInventorySlot& B)
{
	const bool bAEmpty = A.ItemID.IsNone() || A.Count <= 0;
	const bool bBEmpty = B.ItemID.IsNone() || B.Count <= 0;

	if (bAEmpty != bBEmpty)
	{
		return !bAEmpty; // 비어있지 않은 슬롯이 먼저
	}

	return A.ItemID.ToString() < B.ItemID.ToString();
});
}
