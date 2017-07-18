// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceState.h"
#include "Runtime/AIModule/Private/AIModulePrivate.h"
#include "MyEnvQueryManager.h"

//----------------------------------------------------------------------//
// BP functions and related functionality 
//----------------------------------------------------------------------//
UEnvQueryInstanceBlueprintWrapper* UMyEnvQueryManager::MyRunEQSQuery(UObject* WorldContext, UEnvQuery* QueryTemplate, UObject* Querier, TEnumAsByte<EEnvQueryRunMode::Type> RunMode, TSubclassOf<UEnvQueryInstanceBlueprintWrapper> WrapperClass, TArray<float> params)
{
	if (QueryTemplate == nullptr || Querier == nullptr)
	{
		return nullptr;
	}

	TArray<FAIDynamicParam> QueryParams;
	QueryTemplate->CollectQueryParams(*Querier, QueryParams);

	UEnvQueryManager* EQSManager = GetCurrent(WorldContext);
	UEnvQueryInstanceBlueprintWrapper* QueryInstanceWrapper = nullptr;

	if (EQSManager)
	{
		bool bValidQuerier = true;

		// convert controller-owners to pawns, unless specifically configured not to do so
		if (GET_AI_CONFIG_VAR(bAllowControllersAsEQSQuerier) == false && Cast<AController>(Querier))
		{
			AController* Controller = Cast<AController>(Querier);
			if (Controller->GetPawn())
			{
				Querier = Controller->GetPawn();
			}
			else
			{
				UE_VLOG(Controller, LogEQS, Error, TEXT("Trying to run EQS query while not having a pawn! Aborting."));
				bValidQuerier = false;
			}
		}

		if (bValidQuerier)
		{
			QueryInstanceWrapper = NewObject<UEnvQueryInstanceBlueprintWrapper>(EQSManager, (UClass*)(WrapperClass) ? (UClass*)WrapperClass : UEnvQueryInstanceBlueprintWrapper::StaticClass());
			check(QueryInstanceWrapper);
			
			TArray<FEnvNamedValue>* parameters = new TArray<FEnvNamedValue>;

			FEnvQueryRequest QueryRequest(QueryTemplate, Querier);

			if (params.Num() >= QueryParams.Num())
			{
				for (int i = 0; i < QueryParams.Num(); i++)
				{
					QueryParams[i].Value = params[i];
					FEnvNamedValue param;
					param.Value = QueryParams[i].Value;
					param.ParamName = QueryParams[i].ParamName;
					parameters->Add(param);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("You did not provide enough parameters to run the query"));
			}

			QueryRequest.SetNamedParams(*parameters);
			QueryInstanceWrapper->RunQuery(RunMode, QueryRequest);
		}
	}

	return QueryInstanceWrapper;
}



