// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryWidget.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/Border.h"
#include "Inventory/InventoryComponent.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("UInventoryWidget::NativeConstruct()"));
	
	if (!InventoryRef || !InventoryGrid)
	{
		return;
	}

	InventoryGrid->ClearChildren();
	
	const int32 RowCount = InventoryRef->RowCount;
	const int32 ColumnCount = InventoryRef->ColumnCount;
	const int32 SlotCount = RowCount * ColumnCount;
	
	for (int32 i = 0; i < SlotCount; ++i)
	{
		USizeBox* SlotSizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());
		SlotSizeBox->SetWidthOverride(80.0f);
		SlotSizeBox->SetHeightOverride(80.0f);

		UBorder* SlotBorder = WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass());
		SlotBorder->SetBrushColor(FLinearColor(0.08f, 0.08f, 0.08f, 0.85f));
		SlotBorder->SetPadding(FMargin(4.0f));

		SlotSizeBox->AddChild(SlotBorder);

		const int32 Row = i / ColumnCount;
		const int32 Column = i % ColumnCount;

		UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(SlotSizeBox, Row, Column);
		GridSlot->SetHorizontalAlignment(HAlign_Center);
		GridSlot->SetVerticalAlignment(VAlign_Center);
	}
}
