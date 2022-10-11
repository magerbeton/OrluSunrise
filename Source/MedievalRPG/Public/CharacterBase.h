// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UHealthComponent;

UCLASS()
class MEDIEVALRPG_API ACharacterBase : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UHealthComponent* HealthComponent;
};
