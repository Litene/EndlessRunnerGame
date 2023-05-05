// Fill out your copyright notice in the Description page of Project Settings.


#include "FSaveItem.h"

FText FSaveItem::GetText() {
	FString BuiltString;
	BuiltString.Append("Name: ");
	BuiltString.Append(Name);
	
	BuiltString.Append("Score: ");
	BuiltString.Append(FString::FromInt(Score));
	
	return FText::FromString(BuiltString);
}
