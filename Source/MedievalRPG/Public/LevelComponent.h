// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "LifeskillStruct.h"
#include "XpBoostTimerStruct.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int, XpType);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	TArray<int> Levels;

	UPROPERTY()
	TArray<FText> Names;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	TArray<float> CurrentXp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	TArray<float> MaxXp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	float GeneralXpBonus; // temporary buffs which can be started through food or potions

	UPROPERTY()
	TArray<float> SkillXpBonus; //only gets affected by equipment -> perma buffs

	UFUNCTION(BlueprintCallable, Category="XP")
	bool AddXpToSkill(int SkillId, float XpAmount);

	UFUNCTION(BlueprintCallable, Category="Constructor")
	void OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp, TArray<FXpBoostTimerStruct> newActiveXpBoosts);

	UFUNCTION(BlueprintCallable, Category="Levels")
	int GetTotalLevel() const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	FLifeskillStruct GetSkillInfo(int Skill) const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	TArray<FLifeskillStruct> GetAllSkillInfos();

	UFUNCTION(BlueprintCallable, Category="Variables")
	int GetSkillCount() const;

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp LevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	TArray<FXpBoostTimerStruct> ActiveXpBoosts;

	UPROPERTY()
	FTimerHandle ActiveXpBoostTimerHandle;
	
	UFUNCTION()
	void InitializeXpBoosts();

	UFUNCTION()
	void XpBuffFinished();

	UFUNCTION(BlueprintCallable, Category="Xp Boost")
	void SortXpBoostIntoTimeline(FXpBoostTimerStruct XpBoost);

	UFUNCTION()
	void SetNextTimer();

	void ReduceAllTimersBySeconds(float time);

	float CalculateTotalXpBoost();
};
