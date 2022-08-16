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

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *DeathAnimMontage; 

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditDefaultsOnly, Category = "LifeSpan")
    float TimeLifeSpan = 5.0f;

    void MoveForward(float AxisValue);
    void MoveRight(float AxisValue);
    void OnHealthChanged(float NewHealth);
    void OnStartRunning();
    void OnStopRunning();
    void OnDeath();
    

  public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float MovementSpeed = 100.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsAccelerateRunning = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsMovingForward;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetDirection() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION()
    void OnGroundLanded(const FHitResult &Hit);
};
