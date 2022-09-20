// All Copyright belongs to Konstantin Passig


#include "MyPracticeActor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "..\Public\MyPracticeActor.h"


float AMyPracticeActor::CalculateNewHealth(float InHealth, float InDamage)
{
	float NewHealth;

	NewHealth = InHealth - InDamage;

	if (NewHealth <= 0)
	{
		return -1.0f;
	}
	else return NewHealth;
}

// Sets default values
AMyPracticeActor::AMyPracticeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	myString = FString(TEXT("This is my test text in for of a string"));
	mySecondString = FString(TEXT("This is the 2nd text of the second thing"));

	Health = 100.0f;
	Damage = 15.0f;

}

// Called when the game starts or when spawned
void AMyPracticeActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("This is the string in mystring: %s and the second string %s"), *myString, *mySecondString);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString(TEXT("Here is my example text on the main screen")) + FString::FromInt(15));
	Health = CalculateNewHealth(Health, Damage);
	//GEngine->AddOnScreenDebugMessage(0,5.0f, FColor::Cyan, FString::SanitizeFloat(CalculateNewHealth(Health,Damage)))
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Cyan, FString::SanitizeFloat(Health));
}

// Called every frame
void AMyPracticeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


