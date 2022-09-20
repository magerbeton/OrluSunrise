// All Copyright belongs to Konstantin Passig


#include "HeatEffectivityComponent.h"

// Sets default values for this component's properties
UHeatEffectivityComponent::UHeatEffectivityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


float UHeatEffectivityComponent::CalculateHeatEffectivity(float Heat)
{
	return ((2.3258434762117f * pow(10, -14) * pow(Heat, 5)) - (7.5126927328381f * pow(10, -11) * pow(Heat, 4)) + (7.6958244842286f * pow(10, -8) * pow(Heat, 3)) - (2.2334039368342f * pow(10, -5) * pow(Heat, 2)) - (0.0040364392513061f * Heat) + 2.1777106019744);
}

// Called when the game starts

void UHeatEffectivityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHeatEffectivityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

