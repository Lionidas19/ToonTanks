// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasePawn.h"
#include "CoreMinimal.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 50.f;

	void Move(float Value);

	void Turn(float Value);

	APlayerController* TankPlayerController;

public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	class APlayerController* GetTankPlayerController() const {return TankPlayerController;}

	bool bAlive = true;
};
