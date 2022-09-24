// All Copyright belongs to Konstantin Passig


#include "PurseComponent.h"

// Sets default values for this component's properties
UPurseComponent::UPurseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPurseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPurseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UPurseComponent::AddCoinsToPurse(int amount)
{
	if(amount>0)
	{
		AmountOfCoins+=amount;
		UE_LOG(LogTemp,Display,TEXT("Added %i coins. Now in possession: %i coins"),amount,AmountOfCoins);
		return true;
	}
	return false;
}

bool UPurseComponent::SubtractFromPurse(int amount)
{
	if(amount>0)
	{
		if(AmountOfCoins-amount>=0)
		{
			AmountOfCoins-=amount;
			return true;
		}
		return false;
	}
	return false;
}

