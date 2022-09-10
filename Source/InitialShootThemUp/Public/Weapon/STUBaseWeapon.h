// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.h"
#include "STUBaseWeapon.generated.h"

UCLASS()
class INITIALSHOOTTHEMUP_API ASTUBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBaseWeapon();

	virtual void StartFire();
    virtual void StopFire();
    void ChangeClip();
    bool CanReload() const;
    FOnClipEmptySignature OnClipEmpty;

    FWeaponUIData GetUIData() const
    {
        return UIData;
    }

    FAmmoData GetAmmoData() const
    {
        return CurrentAmmo;
    }

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 TraceMaxDistance = 1500;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo {15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

	virtual void BeginPlay() override;

	virtual void MakeShot();

	APlayerController *GetPlayerController() const;
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;
    FVector GetMuzzleWorldLocation() const;

    virtual bool GetTraceData(FVector &OutTraceStart, FVector &OutTraceEnd) const;

    void MakeHit(FHitResult &OutHitResult, const FVector &TraceStart, const FVector &TraceEnd);

    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void LogAmmo();

private:
    FAmmoData CurrentAmmo;
};
