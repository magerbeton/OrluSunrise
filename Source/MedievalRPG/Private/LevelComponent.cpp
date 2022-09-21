// All Copyright belongs to Konstantin Passig


#include "LevelComponent.h"

#include "LifeskillStruct.h"

// Sets default values for this component's properties
ULevelComponent::ULevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TArray<FString> StrNames = {"Holzhacken","Bergbau","Sammeln","Erhitzen","Schmieden","Kampf","Kochen","Herstellen"};
	
	Names.Init(FText(),8);
	
	for(int i = 0; i<StrNames.Num();i++)
	{
		Names[i] = FText::FromString(StrNames[i]);
	}
	UE_LOG(LogTemp,Warning,TEXT("Amount of lifeskills: %i"),Names.Num());
	
	Levels.Init(0,Names.Num());
	CurrentXp.Init(0.0f,Names.Num());
	MaxXp.Init(0.0f,Names.Num());
	GeneralXpBonus = 0.0f;

	
	
	// ...
}


// Called when the game starts
void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void ULevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool ULevelComponent::AddXpToSkill(int SkillId, float XpAmount)
{
	if(CurrentXp.IsValidIndex(SkillId))
	{
		CurrentXp[SkillId] += XpAmount * (1+GeneralXpBonus+SkillXpBonus[SkillId]);
		while(CurrentXp[SkillId]>MaxXp[SkillId])
		{
			Levels[SkillId] += 1;
			CurrentXp[SkillId] -= MaxXp[SkillId];
			UE_LOG(LogTemp,Display,TEXT("Leveled %s up to level %i"),*Names[SkillId].ToString(),Levels[SkillId]);
			LevelUp.Broadcast(SkillId);
		}
		UE_LOG(LogTemp,Display,TEXT("added %f to %s"),XpAmount,*Names[SkillId].ToString());
	}
	return false;
	
}

void ULevelComponent::OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp, TArray<FXpBoostTimerStruct> newActiveXpBoosts)
{
	Levels = newLevels;
	MaxXp = newMaxXp;
	CurrentXp = newCurrentXp;
	ActiveXpBoosts = newActiveXpBoosts;
}

int ULevelComponent::GetTotalLevel() const
{
	int TotalLevel = 0;
	for(const int Level : Levels)
	{
		TotalLevel += Level;
	}
	return TotalLevel;
}

FLifeskillStruct ULevelComponent::GetSkillInfo(int SkillId) const
{
	if(Levels.IsValidIndex(SkillId) && MaxXp.IsValidIndex(SkillId) && CurrentXp.IsValidIndex(SkillId))
	{
		return FLifeskillStruct(SkillId,Levels[SkillId],MaxXp[SkillId],CurrentXp[SkillId]);
	}
	return FLifeskillStruct(SkillId,-1,-1,-1);
	
}

TArray<FLifeskillStruct> ULevelComponent::GetAllSkillInfos()
{
	TArray<FLifeskillStruct> LifeskillStructs;
	for(int i = 0; i<Names.Num();i++)
	{
		if(Levels.IsValidIndex(i)&&MaxXp.IsValidIndex(i)&&CurrentXp.IsValidIndex(i))
		{
			LifeskillStructs.Add(FLifeskillStruct(i,Levels[i],MaxXp[i],CurrentXp[i]));
		}
		else
		{
			LifeskillStructs.Add(FLifeskillStruct(i,-1,-1,-1));
		}
	}
	return LifeskillStructs;
}

int ULevelComponent::GetSkillCount() const
{
	return Levels.Num();
}

void ULevelComponent::InitializeXpBoosts()
{
	
}

void ULevelComponent::XpBuffFinished()
{
	const FXpBoostTimerStruct CurrentBoost = ActiveXpBoosts[0];
	ActiveXpBoosts.RemoveAt(0);
	
	for (FXpBoostTimerStruct& ActiveBoost : ActiveXpBoosts)
	{
		ActiveBoost.RemainingTime -= CurrentBoost.RemainingTime;
	}
	SetNextTimer();
}

void ULevelComponent::SortXpBoostIntoTimeline(FXpBoostTimerStruct XpBoost)
{
	if(GetWorld()->GetTimerManager().IsTimerActive(ActiveXpBoostTimerHandle))
	{
		GetWorld()->GetTimerManager().PauseTimer(ActiveXpBoostTimerHandle);
		const float RemainingTime = GetWorld()->GetTimerManager().GetTimerElapsed(ActiveXpBoostTimerHandle);
		ReduceAllTimersBySeconds(RemainingTime);
	}
	
	ActiveXpBoosts.Add(XpBoost);
	Algo::SortBy(ActiveXpBoosts, &FXpBoostTimerStruct::RemainingTime);

	for(const FXpBoostTimerStruct& XpBoost : ActiveXpBoosts)
	{
		UE_LOG(LogTemp, Display, TEXT("Remaining Time: %f with %f % boost"),XpBoost.RemainingTime,XpBoost.XpBoost);
	}

	SetNextTimer();
}

void ULevelComponent::SetNextTimer()
{
	//GetWorld()->GetTimerManager().GetTimerElapsed(ActiveXpBoostTimerHandle);
	
	if(ActiveXpBoosts.Num()>0)
	{
		GetWorld()->GetTimerManager().SetTimer(ActiveXpBoostTimerHandle,this,&ULevelComponent::XpBuffFinished,ActiveXpBoosts[0].RemainingTime,false);
		UE_LOG(LogTemp,Display,TEXT("Started Xp Boost Timer: %f seconds, %f boost"),ActiveXpBoosts[0].RemainingTime,ActiveXpBoosts[0].XpBoost);
	}
	else
	{
		UE_LOG(LogTemp,Display,TEXT("No Xp boosts active. Not starting the timer again."));
	}

	CalculateTotalXpBoost();
		
}

void ULevelComponent::ReduceAllTimersBySeconds(float time)
{
	for (FXpBoostTimerStruct& ActiveBoost : ActiveXpBoosts)
	{
		ActiveBoost.RemainingTime -= time;
	}
}

float ULevelComponent::CalculateTotalXpBoost()
{
	GeneralXpBonus = 0.0f;
	for(const FXpBoostTimerStruct& ActiveBoost : ActiveXpBoosts)
	{
		GeneralXpBonus += ActiveBoost.XpBoost;
	}
	UE_LOG(LogTemp,Display,TEXT("Total Xp boost is now %f %"),(1+GeneralXpBonus)*100.0f);
	return GeneralXpBonus;
}
