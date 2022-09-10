// Shoot Them Up Game. All Rights Reserved


#include "Components/STUHealthComponent.h"

#include "UI/STUPlayerHUDWidget.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto Owner = GetOwningPlayerPawn();
    if (!Owner) 
    {
        return 0.0f;
    }

    const auto HealtComponent = Cast<USTUHealthComponent>(Owner->GetComponentByClass(USTUHealthComponent::StaticClass()));
    if (!HealtComponent)
    {
        return 0.0f;
    }

    return HealtComponent->GetHealthPercent();
}

