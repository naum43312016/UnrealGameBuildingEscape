// Fill out your copyright notice in the Description page of Project Settings.


#include "MyClass.h"

FString MyClass::getName()
{
	return objName;
}

MyClass::MyClass()
{
}

MyClass::MyClass(FString objName)
{
	this->objName = objName;
}
MyClass::~MyClass()//Destructor
{
}
