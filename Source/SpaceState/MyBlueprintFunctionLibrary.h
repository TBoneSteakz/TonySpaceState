// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Engine/Classes/AI/Navigation/NavLinkDefinition.h"
#include "Runtime/Engine/Public/AI/NavigationModifier.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SPACESTATE_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary 
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintCallable, Category = "AI")
		static float MyGetSightRadius(AActor* Actor);

		UFUNCTION(BlueprintCallable, Category = "AI")
		static void MySetSightRadius(AActor* Actor,float sightRadius);
	
		UFUNCTION(BlueprintCallable, Category = "AI")
		static FVector MyGetNavLinkLeft(AActor* Actor);

		UFUNCTION(BlueprintCallable, Category = "AI")
		static FVector MyGetNavLinkRight(AActor* Actor);
};
