// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SlashUserWidget.h"

void USlashUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

