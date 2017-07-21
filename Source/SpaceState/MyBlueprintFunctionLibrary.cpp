// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceState.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionTypes.h"
#include "Runtime/AIModule/Classes/Perception/AISense.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"

	float UMyBlueprintFunctionLibrary::MyGetSightRadius(AActor * Actor)
	{
		FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

		if (!Id.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
			return 0.00;
		}

		// GetPerception() = AIController->GetPerceptionComponent()
		AAIController* controller = UAIBlueprintHelperLibrary::GetAIController(Actor);
		UAIPerceptionComponent* perceptionComponent = controller->GetPerceptionComponent();
		auto Config = perceptionComponent->GetSenseConfig(Id);
		auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);

		// Save original lose range
		float SightRadius = ConfigSight->SightRadius;

		return SightRadius;
	}

	void UMyBlueprintFunctionLibrary::MySetSightRadius(AActor * Actor, float sightRadius)
	{
		FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

		if (!Id.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Wrong Sense ID"));
		}

		// GetPerception() = AIController->GetPerceptionComponent()
		AAIController* controller = UAIBlueprintHelperLibrary::GetAIController(Actor);
		UAIPerceptionComponent* perceptionComponent = controller->GetPerceptionComponent();
		auto Config = perceptionComponent->GetSenseConfig(Id);
		auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);

		// Save original lose range
		ConfigSight->SightRadius = sightRadius;
	}
