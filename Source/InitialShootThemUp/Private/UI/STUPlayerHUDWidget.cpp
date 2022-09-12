// Shoot Them Up Game. All Rights Reserved

#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "UI/STUPlayerHUDWidget.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = GetHealthComponent();
    if (!HealthComponent)
    {
        return 0.0f;
    }

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData &WeaponUIData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;
    WeaponComponent->GetWeaponUIData(WeaponUIData);
    return true;
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent)
        return false;
    WeaponComponent->GetWeaponAmmoData(AmmoData);
    return true;
}

USTUWeaponComponent * USTUPlayerHUDWidget::GetWeaponComponent() const
{
    const auto Owner = GetOwningPlayerPawn();
    if (!Owner)
    {
        return nullptr;
    }

    const auto WeaponComponent =
        Cast<USTUWeaponComponent>(Owner->GetComponentByClass(USTUWeaponComponent::StaticClass()));

    return WeaponComponent;
}

USTUHealthComponent * USTUPlayerHUDWidget::GetHealthComponent() const
{
    const auto Owner = GetOwningPlayerPawn();
    if (!Owner)
    {
        return nullptr;
    }

    const auto HealthComponent =
        Cast<USTUHealthComponent>(Owner->GetComponentByClass(USTUHealthComponent::StaticClass()));

    return HealthComponent;
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetHealthComponent();
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}