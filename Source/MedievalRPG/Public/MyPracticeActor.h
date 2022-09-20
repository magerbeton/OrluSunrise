// All Copyright belongs to Konstantin Passig

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPracticeActor.generated.h"

UCLASS()
class MEDIEVALRPG_API AMyPracticeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VARs")
		FString myString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "VARs")
		FString mySecondString;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
		float Damage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
		float Health;

	UFUNCTION(BlueprintCallable, Category = "Damage")
		float CalculateNewHealth(float InHealth,float InDamage);

	AMyPracticeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
