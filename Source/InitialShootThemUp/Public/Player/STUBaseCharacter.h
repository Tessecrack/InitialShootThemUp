// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/STUCharacterMovementComponent.h"
#include "STUBaseCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class USTUHealthComponent;
class UTextRenderComponent;

UCLASS()
class INITIALSHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ASTUBaseCharacter(const FObjectInitializer& ObjInit);

  protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent *CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent *SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTUHealthComponent *HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent *HealthTextComponent;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);

    void OnStartRunning();
    void OnStopRunning();

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetDirection() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float MovementSpeed = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsAccelerateRunning = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsMovingForward;
};
