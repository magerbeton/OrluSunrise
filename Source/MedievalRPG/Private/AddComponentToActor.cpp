// All Copyright belongs to Konstantin Passig


#include "AddComponentToActor.h"
#include "GameFramework/Actor.h"	
#include "Components/StaticMeshComponent.h"
//#include "Kismet/KismetTextLibrary.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AAddComponentToActor::AAddComponentToActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//Mesh->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
	Mesh->AttachTo(Root);

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextBar"));
	//TextRender->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::SnapToTargetIncludingScale);
	TextRender->AttachTo(Root);
	TextRender->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextRender->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	//BoxCollision->AttachToComponent(GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	BoxCollision->SetBoxExtent(FVector(10.0f, 10.0f, 25.0f));
	BoxCollision->AttachTo(Root);

	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	TextRender->SetText(TEXT("Test text"));
	*/
	

}

// Called when the game starts or when spawned
void AAddComponentToActor::BeginPlay()
{
	Super::BeginPlay();
	/*
	TextRender->SetRelativeLocation(FVector(0.0f, 0.0f, TextOffset));
	CurrentLocation = Mesh->GetRelativeLocation();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAddComponentToActor::OnBoxOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAddComponentToActor::OnBoxOverlapEnd);
	*/
	//OnActorBeginOverlap.AddDynamic(this, &AAddComponentToActor::OnBoxOverlapBegin);

}

// Called every frame
void AAddComponentToActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Mesh->SetRelativeLocation(CurrentLocation+FVector(0.0f,0.0f,10.0f*DeltaTime));
	//CurrentLocation = Mesh->GetRelativeLocation();
	//SetActorRotation(GetActorRotation()+ FRotator(0.0f,0.0f,10.0f*DeltaTime));
	//SetActorLocation(GetActorLocation() + FVector(0.0f, 10.0f * DeltaTime, 0.0f));
	//TextRender->SetText(FString::SanitizeFloat(DeltaTime));
}
/*
void AAddComponentToActor::RandomFunciton()
{
}

void AAddComponentToActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	FString ActorName = OtherActor->GetActorLabel();
	FText OutputText = UKismetTextLibrary::Conv_StringToText(ActorName);
	TextRender->SetText(OutputText);
	SetActorLocation(GetActorLocation() + FVector(0.0f, 0.0f, 50.0f));
	
	//TextRender->SetText(TEXT("Overlap"));
	
}

void AAddComponentToActor::OnBoxOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	FString ActorName = OtherActor->GetActorLabel();
	FText OutputText = UKismetTextLibrary::Conv_StringToText(ActorName);
	TextRender->SetText(OutputText);
	
}
*/


