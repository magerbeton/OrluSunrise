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
	
	Levels.Init(0,Names.Num());
	CurrentXp.Init(0.0f,Names.Num());
	MaxXp.Init(0.0f,Names.Num());

	
	
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
		CurrentXp[SkillId] += XpAmount;
		while(CurrentXp[SkillId]>MaxXp[SkillId])
		{
			Levels[SkillId] += 1;
			CurrentXp[SkillId] -= MaxXp[SkillId];
			UE_LOG(LogTemp,Display,TEXT("Leveled %s up to level %i"),*Names[SkillId].ToString(),Levels[SkillId]);
		}
		UE_LOG(LogTemp,Display,TEXT("added %f to %s"),XpAmount,*Names[SkillId].ToString());
	}
	return false;
	
}

void ULevelComponent::OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp)
{
	Levels = newLevels;
	MaxXp = newMaxXp;
	CurrentXp = newCurrentXp;
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
	return FLifeskillStruct(SkillId,Levels[SkillId],MaxXp[SkillId],CurrentXp[SkillId]);
}

TArray<FLifeskillStruct> ULevelComponent::GetAllSkillInfos()
{
	TArray<FLifeskillStruct> LifeskillStructs;
	for(int i = 0; i<Names.Num();i++)
	{
		LifeskillStructs.Add(FLifeskillStruct(i,Levels[i],MaxXp[i],CurrentXp[i]));
	}
	return LifeskillStructs;
}

int ULevelComponent::GetSkillCount() const
{
	return Levels.Num();
}

