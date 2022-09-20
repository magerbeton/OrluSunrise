// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "LifeskillStruct.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALRPG_API ULevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULevelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	TArray<int> Levels;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY()
	TArray<float> CurrentXp;

	UPROPERTY()
	TArray<float> MaxXp;

	UPROPERTY()
	float GeneralXpBonus;

	UPROPERTY()
	TArray<float> SkillXpBonus;

	UFUNCTION(BlueprintCallable, Category="XP")
	bool AddXpToSkill(int SkillId, float XpAmount);

	UFUNCTION(BlueprintCallable, Category="Constructor")
	void OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp);

	UFUNCTION(BlueprintCallable, Category="Levels")
	int GetTotalLevel() const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	FLifeskillStruct GetSkillInfo(int Skill) const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	TArray<FLifeskillStruct> GetAllSkillInfos();

	UFUNCTION(BlueprintCallable, Category="Variables")
	int GetSkillCount() const;

	
};
