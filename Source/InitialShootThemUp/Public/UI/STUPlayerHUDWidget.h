// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "STUCoreTypes.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.generated.h"

class USTUWeaponComponent;
class USTUHealthComponent;

UCLASS()
class INITIALSHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData &WeaponUIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

private: 
    USTUWeaponComponent *GetWeaponComponent() const;
    USTUHealthComponent *GetHealthComponent() const;
};
