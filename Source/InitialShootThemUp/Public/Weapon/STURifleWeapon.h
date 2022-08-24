// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class INITIALSHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
	virtual void StopFire() override;

protected:
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &OutTraceStart, FVector &OutTraceEnd) const override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

private:
    FTimerHandle ShotTimerHandle;
};
