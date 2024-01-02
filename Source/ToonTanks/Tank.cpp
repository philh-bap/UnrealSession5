// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}


void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);
		Rotateurret(HitResult.ImpactPoint);
		/*DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			25,
			12,
			FColor::Red,
			false,
			-1
		);*/
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef = Cast<APlayerController>(GetController());
	DrawDebugSphere(
		GetWorld(),
		GetActorLocation() + FVector(0, 0, 200),
		100,
		12,
		FColor::Red,
		true,
		30
	);
}

void ATank::Move(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move %f"), Value);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation);
}

void ATank::Turn(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Turn %f"), Value);
	FRotator DeltaLocation = FRotator::ZeroRotator;

	DeltaLocation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaLocation);


}