// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SlashEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/SlashAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
ASlashEffectActor::ASlashEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void ASlashEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const USlashAttributeSet* SlashAttributeSet = Cast<USlashAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(USlashAttributeSet::StaticClass()));
 
		USlashAttributeSet* MutableSlashAttributeSet = const_cast<USlashAttributeSet*>(SlashAttributeSet);
		MutableSlashAttributeSet->SetHealth(SlashAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ASlashEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called when the game starts or when spawned
void ASlashEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ASlashEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ASlashEffectActor::EndOverlap);
}

