#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DoorActor.h"

APressurePlate::APressurePlate()
{
    PrimaryActorTick.bCanEverTick = false;

    PlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlateMesh"));
    RootComponent = PlateMesh;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetBoxExtent(FVector(50.f, 50.f, 10.f));
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
}

void APressurePlate::BeginPlay()
{
    Super::BeginPlay();

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor || OtherActor == this) return;

    CurrentActors++;
    if (CurrentActors >= RequiredActors)
    {
        if (ADoorActor* Door = Cast<ADoorActor>(LinkedDoor))
        {
            Door->OpenDoor();
        }
    }
}

void APressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!OtherActor || OtherActor == this) return;

    CurrentActors = FMath::Max(0, CurrentActors - 1);
    if (CurrentActors < RequiredActors)
    {
        if (ADoorActor* Door = Cast<ADoorActor>(LinkedDoor))
        {
            Door->CloseDoor();
        }
    }
}
