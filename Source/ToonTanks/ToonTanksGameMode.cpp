// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor*  DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
			/*Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;*/
		}
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		UE_LOG(LogTemp, Display, TEXT("Destroyed Tower: %s"), *DestroyedTower->GetName());
	}
	else
	{
		// Log the type of the DeadActor
		UE_LOG(LogTemp, Warning, TEXT("Dead Actor is of type: %s"), *DeadActor->GetClass()->GetName());
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerTimerDelegate = FTimerDelegate::CreateUObject(
		ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true 
		);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			PlayerTimerDelegate,
			StartDelay,
			false);
	}
}

void AToonTanksGameMode::StartGame()
{

}