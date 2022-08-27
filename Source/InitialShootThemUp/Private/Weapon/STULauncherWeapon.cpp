// Shoot Them Up Game. All Rights Reserved


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjecttile.h"

void ASTULauncherWeapon::StartFire() 
{
    MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
    if (!GetWorld())
    {
        return;
    }
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        return;
    }
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ASTUProjecttile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjecttile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}