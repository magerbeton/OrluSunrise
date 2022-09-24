// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PurseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEDIEVALRPG_API UPurseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPurseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category="Coins")
	int AmountOfCoins;

	UFUNCTION(BlueprintCallable,Category="Coins")
	bool AddCoinsToPurse(int amount);

	UFUNCTION(BlueprintCallable, Category="Coins")
	bool SubtractFromPurse(int amount);
};
