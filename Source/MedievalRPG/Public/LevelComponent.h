// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "BoosterStruct.h"
#include "LifeskillStruct.h"
#include "XpTypeEnum.h"
#include "Components/ActorComponent.h"
#include "LevelComponent.generated.h"

class UBuffComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, EXpTypeEnum, XpType);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InitialVariables")
	UBuffComponent* XpBuffComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="InitialVariables")
	UAudioComponent* AudioComponent;
	
	UPROPERTY()
	TArray<float> SkillXpBonus; //only gets affected by equipment -> perma buffs

	UFUNCTION(BlueprintCallable, Category="XP")
	//bool AddXpToSkill(int SkillId, float XpAmount);
	bool AddXpToSkill(EXpTypeEnum XpType, float XpAmount);

	UFUNCTION(BlueprintCallable, Category="Constructor")
	void OverwriteData(TArray<int> newLevels, TArray<float> newMaxXp, TArray<float> newCurrentXp, UBuffComponent* XpBuffComp);

	UFUNCTION(BlueprintCallable, Category="Levels")
	int GetTotalLevel() const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	FLifeskillStruct GetSkillInfo(EXpTypeEnum XpType) const;

	UFUNCTION(BlueprintCallable, Category="Variables")
	TArray<FLifeskillStruct> GetAllSkillInfos();

	UFUNCTION(BlueprintCallable, Category="Variables")
	int GetSkillCount() const;

	UPROPERTY(BlueprintAssignable)
	FOnLevelUp LevelUp;

	UPROPERTY()
	USoundBase* LevelUpSound;

	void PlayLevelupSound() const;
};
