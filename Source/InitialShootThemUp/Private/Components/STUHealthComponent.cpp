// Shoot Them Up Game. All Rights Reserved


#include "Components/STUHealthComponent.h"
DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    SetHealth(MaxHealth);

	AActor *OwnerComponent = GetOwner();
    if (OwnerComponent)
    {
        OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                              AController *InstigatedBy, AActor *DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
    {
        return;
    }
    SetHealth(Health - Damage);
    if (IsDead())
    {
        OnDeath.Broadcast();
        return;
    }
    else if (AutoHeal)
    {
        ResetTimerAutoHeal();
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}
void USTUHealthComponent::HealUpdate()
{
    if (IsDead())
    {
        ResetTimerAutoHeal();
        return;
    }
    SetHealth(Health + HealModifier);
    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        ResetTimerAutoHeal();
    }
}

void USTUHealthComponent::ResetTimerAutoHeal()
{
    if (GetWorld()->GetTimerManager().IsTimerActive(HealTimerHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
