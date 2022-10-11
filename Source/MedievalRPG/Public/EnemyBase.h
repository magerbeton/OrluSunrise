// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.h"
#include "EnemyStruct.h"
#include "ExperienceInterface.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UHealthComponent; class UPurseComponent; class UInventoryComponent;

UCLASS()
class MEDIEVALRPG_API AEnemyBase : public ACharacter, public IDamageInterface, public IExperienceInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY()
	FEnemyStruct EnemyConfig;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Damage(AActor* InflictingActor, float Amount);
	virtual void Damage_Implementation(AActor* InflictingActor, float Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MovementDebuff(AActor* InflictingActor, bool HeavyHit, bool SmackDown);
	virtual void MovementDebuff_Implementation(AActor* InflictingActor, bool HeavyHit, bool SmackDown);

	UPROPERTY()
	FTimerHandle MovementLockTimerHandle;

	UFUNCTION()
	bool InflictMovementBreak(float Time);

	UFUNCTION()
	void ReenableMovement();
	
	UFUNCTION()
	void OnDeath();

	UPROPERTY()
	AActor* ActorToReceiveXp;

	UPROPERTY()
	UPurseComponent* PurseComponent;

	UPROPERTY()
	UInventoryComponent* ItemsToDrop;
	
};
