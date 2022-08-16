// Shoot Them Up Game. All Rights Reserved

#include "Player/STUBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer &ObjInit)
    : Super(
          ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");

    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset.Z = 90;

    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->bUsePawnControlRotation = false;

    HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    (*HealthTextComponent).SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
    check(GetCharacterMovement());
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ASTUBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTUBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ASTUBaseCharacter::OnGroundLanded);
}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookHorizontal", this, &ASTUBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookVertical", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUBaseCharacter::OnStopRunning);
}

void ASTUBaseCharacter::MoveForward(float AxisValue)
{
    IsMovingForward = AxisValue > 0.0f;
    AddMovementInput(GetActorForwardVector(), AxisValue * MovementSpeed);
}

void ASTUBaseCharacter::MoveRight(float AxisValue)
{
    AddMovementInput(GetActorRightVector(), AxisValue * MovementSpeed);
}

void ASTUBaseCharacter::OnStartRunning()
{
    IsAccelerateRunning = true;
}

void ASTUBaseCharacter::OnStopRunning()
{
    IsAccelerateRunning = false;
}

bool ASTUBaseCharacter::IsRunning() const
{
    return IsAccelerateRunning && IsMovingForward && !GetVelocity().IsZero();
}

void ASTUBaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    const auto FallVelocityZ = FMath::Abs(GetCharacterMovement()->Velocity.Z);
    
    if (FallVelocityZ < LandedDamageVelocity.X)
    {
        return;
    }

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);

    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

float ASTUBaseCharacter::GetDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;

    const FVector ForwardVector = GetActorForwardVector();
    const FVector VelocityNormalVector = GetVelocity().GetSafeNormal();
    const float AngleRadians = FMath::Acos(FVector::DotProduct(ForwardVector, VelocityNormalVector));

    const FVector CrossProduct = FVector::CrossProduct(ForwardVector, VelocityNormalVector);

    const float Degrees = FMath::RadiansToDegrees(AngleRadians);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTUBaseCharacter::OnDeath() 
{
    PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(TimeLifeSpan);
    if (Controller) 
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ASTUBaseCharacter::OnHealthChanged(float NewHealth)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}