// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "BoosterStruct.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBuffRanOut);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALRPG_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Variables")
	float TotalBoost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	TArray<FBoosterStruct> ActiveBoosts;

	UPROPERTY()
	FTimerHandle ActiveBoostTimerHandle;
	
	UFUNCTION(BlueprintCallable, Category="VariableInit")
	void InitializeBoosts(TArray<FBoosterStruct> Boosters);

	UFUNCTION()
	void BoostFinished();

	UFUNCTION(BlueprintCallable, Category="Functions")
	void AddBoost(FBoosterStruct Booster);
	
	void SortBoostIntoTimeline(FBoosterStruct Booster);

	UFUNCTION()
	void SetNextTimer();

	void ReduceAllTimersBySeconds(float time);

	float CalculateTotalXpBoost();

	UPROPERTY(BlueprintAssignable)
	FBuffRanOut BuffRanOut;
		
};
