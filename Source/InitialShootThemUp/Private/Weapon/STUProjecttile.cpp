// Shoot Them Up Game. All Rights Reserved

#include "Weapon/STUProjecttile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTUProjecttile::ASTUProjecttile()
{
    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

void ASTUProjecttile::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent);
    check(MovementComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTUProjecttile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ASTUProjecttile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                      UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!GetWorld())
    {
        return;
    }
    MovementComponent->StopMovementImmediately();

    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadius, UDamageType::StaticClass(), 
        {GetOwner()}, this, GetController(), DoFullDamage);

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Orange, false, 2.0f, 0, 1.0f);

    Destroy();
}

AController* ASTUProjecttile::GetController() const
{
    const auto OwnerPawn = Cast<APawn>(GetOwner());
    return OwnerPawn ? OwnerPawn->GetController() : nullptr;
}