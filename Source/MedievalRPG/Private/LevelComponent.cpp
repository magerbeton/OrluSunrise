// All Copyright belongs to Konstantin Passig


#include "LevelComponent.h"

#include "BoosterStruct.h"
#include "BuffComponent.h"
#include "LifeskillStruct.h"
#include "Components/AudioComponent.h"

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
	MaxXp.Init(100.0f,Names.Num());
	SkillXpBonus.Init(0.0f,Names.Num());
	GeneralXpBonus = 0.0f;

	const ConstructorHelpers::FObjectFinder<USoundBase>LevelUpSoundObject(TEXT("SoundCue'/Game/Sounds/ButtonSound/ButtonSound_Cue.ButtonSound_Cue'"));
	if(LevelUpSoundObject.Succeeded())
	{
		LevelUpSound = LevelUpSoundObject.Object;
	}

	
	
	// ...
}


// Called when the game starts
void ULevelComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

	TArray<UActorComponent*> BuffComponents;
	GetOwner()->GetComponents(UBuffComponent::StaticClass(),BuffComponents,false);
	for(UActorComponent* BuffComp : BuffComponents)
	{
		if(BuffComp->ComponentHasTag(FName("XpBoost")))
		{
			XpBuffComponent = Cast<UBuffComponent>(BuffComp);
		}
	}
}


// Called every frame
void ULevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*bool ULevelComponent::AddXpToSkill(int SkillId, float XpAmount)
{
    //GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Cyan,FString::Printf(TEXT("Skill ID: %i, CurrentXpLen: %i, MaxXpLen: %i, Levels: %i"),SkillId,CurrentXp.Num(),MaxXp.Num(),Levels.Num()));
	//UE_LOG(LogTemp,Display,TEXT("Skill ID: %i, CurrentXpLen: %i, MaxXpLen: %i, Levels: %i"),SkillId,CurrentXp.Num(),MaxXp.Num(),Levels.Num());
	
	if(CurrentXp.IsValidIndex(SkillId))
	{
		if(!XpBuffComponent->IsValidLowLevel())
		{
			UE_LOG(LogTemp,Warning,TEXT("Buffcomponent is missing in %s"),__func__);
			return false;
		}
		const float TotalXpBoost = XpBuffComponent->CalculateTotalXpBoost();
		CurrentXp[SkillId] += XpAmount * (1+TotalXpBoost+SkillXpBonus[SkillId]);
		if(abs(MaxXp[SkillId]) != 0.0f)
		{
			while(CurrentXp[SkillId]>MaxXp[SkillId])
			{
				Levels[SkillId] += 1;
				CurrentXp[SkillId] -= MaxXp[SkillId];
				UE_LOG(LogTemp,Display,TEXT("Leveled %s up to level %i"),*Names[SkillId].ToString(),Levels[SkillId]);
				LevelUp.Broadcast(SkillId);
			}
			UE_LOG(LogTemp,Display,TEXT("added %f to %s"),XpAmount,*Names[SkillId].ToString());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Max xp for lifeskill %s is 0"),*Names[SkillId].ToString());
		}
	}
	return false;
	
}*/

bool ULevelComponent::AddXpToSkill(EXpTypeEnum XpType, float XpAmount)
{
	int SkillId = static_cast<uint8>(XpType);
	UE_LOG(LogTemp,Display,TEXT("SkillID = %i"),SkillId);
	if(CurrentXp.IsValidIndex(SkillId))
	{
		if(!XpBuffComponent->IsValidLowLevel())
		{
			UE_LOG(LogTemp,Warning,TEXT("Buffcomponent is missing"));
			return false;
		}
		
		const float TotalXpBoost = XpBuffComponent->CalculateTotalXpBoost();
		CurrentXp[SkillId] += XpAmount * (1+TotalXpBoost+SkillXpBonus[SkillId]);
		if(abs(MaxXp[SkillId]) != 0.0f)
		{
			while(CurrentXp[SkillId]>MaxXp[SkillId])
			{
				Levels[SkillId] += 1;
				CurrentXp[SkillId] -= MaxXp[SkillId];
				UE_LOG(LogTemp,Display,TEXT("Leveled %s up to level %i"),*Names[SkillId].ToString(),Levels[SkillId]);
				LevelUp.Broadcast(XpType);
				PlayLevelupSound();
			}
			UE_LOG(LogTemp,Display,TEXT("added %f to %s"),XpAmount,*Names[SkillId].ToString());
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("Max xp for lifeskill %s is 0"),*Names[SkillId].ToString());
		}
	}
	return false;
}

void ULevelComponent::OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp, UBuffComponent* XpBuffComp)
{
	Levels = newLevels;
	MaxXp = newMaxXp;
	CurrentXp = newCurrentXp;
	XpBuffComponent = XpBuffComp;
	
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

FLifeskillStruct ULevelComponent::GetSkillInfo(EXpTypeEnum EXpType) const
{
	int SkillId = static_cast<uint32>(EXpType);
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

void ULevelComponent::PlayLevelupSound() const
{
	if(AudioComponent->IsValidLowLevel())
	{
		AudioComponent->SetSound(LevelUpSound);
		AudioComponent->Play();
	}
}
