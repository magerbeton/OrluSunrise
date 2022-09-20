// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HeatEffectivityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALRPG_API UHeatEffectivityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHeatEffectivityComponent();

	UFUNCTION(BlueprintCallable, Category = "Smithing", BlueprintPure, meta=(Keywords="Calculates the Heat effectivity while smithing"))
		float CalculateHeatEffectivity(float Heat);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
