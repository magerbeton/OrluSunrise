// All Copyright belongs to Konstantin Passig


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bAllowRegeneration = true;
	TimeBetweenHeal = 0.5f;
	TimeTillRegenerate = 5.0f; //time between damage and start of regenerating
	
	// ...
}

void UHealthComponent::SetupValues(float newHealth, float newMaxHealth)
{
	Health = newHealth;
	MaxHealth = newMaxHealth;
}

void UHealthComponent::SetupValuesRegeneration(float newTimeBetweenHeal, float newHealthPerSecond)
{
	if(bAllowRegeneration)
	{
		TimeBetweenHeal = newTimeBetweenHeal;
		HealthPerSecond = newHealthPerSecond;
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Regeneration is not allowed for %s"),*GetName());
	}
}


bool UHealthComponent::IsRegenerationAllowed() const
{
	return bAllowRegeneration;
}

void UHealthComponent::EnableRegeneration()
{
	bAllowRegeneration = true;
}

void UHealthComponent::DisableRegeneration()
{
	bAllowRegeneration = false;
}

float UHealthComponent::GetMaxHealth() const
{
	return  MaxHealth;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}


void UHealthComponent::TimerHeal()
{
	const float ActualHeal = HealthPerSecond*TimeBetweenHeal;

	Heal(HealthPerSecond*TimeBetweenHeal);

	UE_LOG(LogTemp,Display,TEXT("%s healed by %f to %f"),*GetName(),ActualHeal,Health);
	
	if(Health == MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
		UE_LOG(LogTemp,Display,TEXT("%s finished regenerating"),*GetName());
		return;
	}
	
}

float UHealthComponent::TakeDamage(float Amount)
{
	if(Amount > 0)
	{
		Health -= Amount;
		if(Health <= 0)
		{
			UE_LOG(LogTemp,Warning,TEXT("%s died"),*GetName());
			OnPlayerDie.Broadcast();
			//die
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimer(TimeTillRegenerateHandle,this,&UHealthComponent::StartRegenerate,TimeTillRegenerate,false);
			UE_LOG(LogTemp,Display,TEXT("%s started wait till allowed to regenerate timer"),*GetName());
			if(GetWorld()->GetTimerManager().TimerExists(RegenTimerHandle))
			{
				GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
				UE_LOG(LogTemp,Warning,TEXT("%s stopped currently running regeneration"),*GetName());
			}
		}
	}
	return Health;
}

/**
 * @brief 
 * @param Amount Amount of HP to heal
 * @return new amount of health
 */
float UHealthComponent::Heal(float Amount)
{
	if(Amount > 0)
	{
		Health = FMath::Clamp(Health+Amount,0.0f,MaxHealth);
	}
	return Health;
}

void UHealthComponent::StartRegenerate()
{
	if(!GetWorld()->GetTimerManager().TimerExists(RegenTimerHandle) && !GetWorld()->GetTimerManager().IsTimerActive(RegenTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(RegenTimerHandle,this,&UHealthComponent::TimerHeal,TimeBetweenHeal,true);
	}
}

void UHealthComponent::StopRegenerate()
{
	if(GetWorld()->GetTimerManager().TimerExists(RegenTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimerHandle);
	}
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

