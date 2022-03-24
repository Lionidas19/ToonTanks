// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );

        RotateTurret(HitResult.ImpactPoint);
    }

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
    FVector DeltaLocation(0.f);
    //X = Value * DeltaTime * Speed
    DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * Speed;
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;

    AddActorLocalRotation(DeltaRotation, true);
}