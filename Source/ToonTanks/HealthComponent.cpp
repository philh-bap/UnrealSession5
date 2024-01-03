// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"
// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);

	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	class AController* Instigator, AActor* DamageCauser)
{
	if (Damage < 0 || !DamagedActor) return;

	Health -= Damage;

	FString ActorName = DamagedActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Actor %s took damage. Health: %f"), *ActorName, Health);

	if (Health < 0 && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
	// Log name object receive damage
	/*if (DamagedActor)
	{
		FString ActorName = DamagedActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Actor %s took damage. Health: %f"), *ActorName, Health);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unknown actor took damage. Health: %f"), Health);
	}*/
}



























// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
