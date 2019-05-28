// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BUILDINGESCAPE_API MyClass
{
	FString objName;
public:
	FString getName();
	MyClass();
	MyClass(FString objName);
	~MyClass();
};
