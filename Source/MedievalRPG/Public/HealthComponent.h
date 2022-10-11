// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class 
 UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY()
	float Health;

	UPROPERTY()
	float MaxHealth;

	UFUNCTION(BlueprintCallable, Category="Constructor")
	void SetupValues(float newHealth, float newMaxHealth);

	UFUNCTION(BlueprintCallable, Category="Constructor")
	void SetupValuesRegeneration(float newTimeBetweenHeal, float newHealthPerSecond);

	UPROPERTY()
	float TimeBetweenHeal;

	UPROPERTY()
	float HealthPerSecond;

	UPROPERTY()
	bool bAllowRegeneration;

	UFUNCTION(BlueprintCallable, Category="Variables")
	bool IsRegenerationAllowed() const;

	UFUNCTION(BlueprintCallable, Category="Regeneration")
	void EnableRegeneration();

	UFUNCTION(BlueprintCallable, Category="Regeneration")
	void DisableRegeneration();

	UFUNCTION(BlueprintCallable, Category="Variables")
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="Variables")
	float GetHealth() const;
	
	UPROPERTY()
	float TimeTillRegenerate;
	
	UPROPERTY()
	FTimerHandle TimeTillRegenerateHandle;
	
	UPROPERTY()
	FTimerHandle RegenTimerHandle;

	void TimerHeal();
	
	UFUNCTION(BlueprintCallable, Category="Damage")
	float TakeDamage(float Amount);

	UFUNCTION(BlueprintCallable, Category="Damage")
	float Heal(float Amount);

	UFUNCTION()
	void StartRegenerate();

	UFUNCTION()
	void StopRegenerate();

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDie OnPlayerDie;

	UFUNCTION(BlueprintCallable, Category="Health")
	bool HasDied() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
