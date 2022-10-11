// All Copyright belongs to Konstantin Passig


#include "EnemyBase.h"

#include "BaseItem.h"
#include "ExperienceInterface.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "MoneyInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyConfig = FEnemyStruct(1);
	const ConstructorHelpers::FObjectFinder<UCurveFloat>MaxHealthCurve_Obj(TEXT("CurveFloat'/Game/Data/FCUR_MaxHealth_Base.FCUR_MaxHealth_Base'"));
	if(MaxHealthCurve_Obj.Succeeded())
	{
		EnemyConfig.MaxHealthCurve = MaxHealthCurve_Obj.Object;
	}
	
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	bool HealthSuccess;
	HealthComponent->SetupValues(EnemyConfig.GetMaxHealth(HealthSuccess),EnemyConfig.GetMaxHealth(HealthSuccess)); // always spawn enemy full health
	HealthComponent->OnPlayerDie.AddDynamic(this,&AEnemyBase::OnDeath);
	if(!HealthSuccess)
	{
		UE_LOG(LogTemp,Warning,TEXT("Enemy could not generate health as the enemy struct has no health curve initialized!"));
	}

	ItemsToDrop = CreateDefaultSubobject<UInventoryComponent>(TEXT("ItemsToDrop"));
	ItemsToDrop->NumberOfSlots = 25;
	
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyBase::Damage_Implementation(AActor* InflictingActor, float Amount)
{
	UE_LOG(LogTemp,Display,TEXT("Took Damage %f"),Amount);
	HealthComponent->TakeDamage(Amount);
	if(HealthComponent->HasDied())
	{
		ActorToReceiveXp = InflictingActor;
	}
	
}

void AEnemyBase::MovementDebuff_Implementation(AActor* InflictingActor, bool HeavyHit, bool SmackDown)
{
	if(SmackDown)
	{
		GetMovementComponent()->Deactivate();
		return;
	}
	if(HeavyHit)
	{
		GetMovementComponent()->Deactivate();
		return;
	}
}

bool AEnemyBase::InflictMovementBreak(float Time)
{
	if(Time > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(MovementLockTimerHandle,this, &AEnemyBase::ReenableMovement,2.0f,false);
		return true;
	}
	return false;
}

void AEnemyBase::ReenableMovement()
{
	GetCharacterMovement()->Activate();
}

void AEnemyBase::OnDeath()
{
	if(!ActorToReceiveXp->IsValidLowLevel())
	{
		return;
	}
	
	
	const IExperienceInterface* XpInterface = Cast<IExperienceInterface>(ActorToReceiveXp);
	if(XpInterface)
	{
		bool Success;
		XpInterface->Execute_AddXpToSkill(this,EXpTypeEnum::Combat,EnemyConfig.GetXp(Success));
	}

	const IMoneyInterface* MoneyInterface = Cast<IMoneyInterface>(ActorToReceiveXp);
	if(MoneyInterface)
	{
		MoneyInterface->Execute_TransferMoneyTo(this,nullptr,EnemyConfig.Money);
	}
	
}
