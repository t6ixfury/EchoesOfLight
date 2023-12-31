// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_Interact.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Interfaces/Interface_Interaction.h"

void UW_Interact::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgressBar");
}

void UW_Interact::NativeConstruct()
{
	Super::NativeConstruct();
	
	KeyPressText->SetText(FText::FromString("Press"));


}


void UW_Interact::UpdateWidget(const FInteractableData* InteractionData) const
{
	switch (InteractionData->InteractableType)
	{
	case EInteractableType::Pickup:
		KeyPressText->SetText(FText::FromString("Press"));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);

		if (InteractionData->Quantity < 2)
		{
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"), InteractionData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);

		}
		break;

	case EInteractableType::NonPlayerCharcter:
		break;

	case EInteractableType::Device:
		break;

	case EInteractableType::Toggle:
		break;

	case EInteractableType::Container:
		break;

	}

	ActionText->SetText(InteractionData->Action);
	NameText->SetText(InteractionData->Name);
}

float UW_Interact::UpdateInteractionProgressBar()
{
	return 0.0f;
}

