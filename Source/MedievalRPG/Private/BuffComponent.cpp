// All Copyright belongs to Konstantin Passig


#include "BuffComponent.h"

// Sets default values for this component's properties
UBuffComponent::UBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuffComponent::InitializeBoosts(TArray<FBoosterStruct> Boosters)
{
	ActiveBoosts.Empty();
	for(FBoosterStruct& Boost : Boosters)
	{
		ActiveBoosts.Add(Boost);
	}

	Algo::SortBy(ActiveBoosts, &FBoosterStruct::RemainingTime);
	SetNextTimer();
}

void UBuffComponent::BoostFinished()
{
	const FBoosterStruct CurrentBoost = ActiveBoosts[0];
	ActiveBoosts.RemoveAt(0);
	
	for (FBoosterStruct& ActiveBoost : ActiveBoosts)
	{
		ActiveBoost.RemainingTime -= CurrentBoost.RemainingTime;
	}
	BuffRanOut.Broadcast();
	SetNextTimer();
}

void UBuffComponent::AddBoost(FBoosterStruct Booster)
{
	SortBoostIntoTimeline(Booster);
}

void UBuffComponent::SortBoostIntoTimeline(FBoosterStruct Booster)
{
	if(GetWorld()->GetTimerManager().IsTimerActive(ActiveBoostTimerHandle))
	{
		GetWorld()->GetTimerManager().PauseTimer(ActiveBoostTimerHandle);
		const float RemainingTime = GetWorld()->GetTimerManager().GetTimerElapsed(ActiveBoostTimerHandle);
		ReduceAllTimersBySeconds(RemainingTime);
	}
	
	ActiveBoosts.Add(Booster);
	Algo::SortBy(ActiveBoosts, &FBoosterStruct::RemainingTime);

	for(const FBoosterStruct& XpBoost : ActiveBoosts)
	{
		UE_LOG(LogTemp, Display, TEXT("Remaining Time: %f with %f % boost"),XpBoost.RemainingTime,XpBoost.Boost);
	}

	SetNextTimer();
}

void UBuffComponent::SetNextTimer()
{
	//GetWorld()->GetTimerManager().GetTimerElapsed(ActiveXpBoostTimerHandle);
	
	if(ActiveBoosts.Num()>0)
	{
		GetWorld()->GetTimerManager().SetTimer(ActiveBoostTimerHandle,this,&UBuffComponent::BoostFinished,ActiveBoosts[0].RemainingTime,false);
		UE_LOG(LogTemp,Display,TEXT("Started Boost Timer: %f seconds, %f boost"),ActiveBoosts[0].RemainingTime,ActiveBoosts[0].Boost);
	}
	else
	{
		UE_LOG(LogTemp,Display,TEXT("No boosts active. Not starting the timer again."));
	}

	CalculateTotalXpBoost();
		
}

void UBuffComponent::ReduceAllTimersBySeconds(float time)
{
	for (FBoosterStruct& ActiveBoost : ActiveBoosts)
	{
		ActiveBoost.RemainingTime -= time;
	}
}

float UBuffComponent::CalculateTotalXpBoost()
{
	TotalBoost = 0.0f;
	for(const FBoosterStruct& ActiveBoost : ActiveBoosts)
	{
		TotalBoost += ActiveBoost.Boost;
	}
	UE_LOG(LogTemp,Display,TEXT("Total Xp boost is now %f %"),(1+TotalBoost)*100.0f);
	return TotalBoost;
}

