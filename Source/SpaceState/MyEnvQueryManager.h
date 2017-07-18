// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnvironmentQuery/EnvQueryManager.h"
#include "Runtime/AIModule/Classes/EnvironmentQuery/EnvQuery.h"
#include "MyEnvQueryManager.generated.h"

/**
 * 
 */
UCLASS()
class SPACESTATE_API UMyEnvQueryManager : public UEnvQueryManager
{
	GENERATED_BODY()

public:
			UFUNCTION(BlueprintCallable, Category = "AI|EQS", meta = (WorldContext = "WorldContext", AdvancedDisplay = "WrapperClass"))
		static UEnvQueryInstanceBlueprintWrapper* MyRunEQSQuery(UObject* WorldContext, UEnvQuery* QueryTemplate, UObject* Querier, TEnumAsByte<EEnvQueryRunMode::Type> RunMode, TSubclassOf<UEnvQueryInstanceBlueprintWrapper> WrapperClass,TArray<float> params);
	
	
	
	
};
