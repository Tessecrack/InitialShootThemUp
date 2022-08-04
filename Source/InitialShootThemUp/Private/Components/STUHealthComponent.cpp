// Shoot Them Up Game. All Rights Reserved


#include "Components/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor *OwnerComponent = GetOwner();
    if (OwnerComponent)
    {
        OwnerComponent->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                              AController *InstigatedBy, AActor *DamageCauser)
{
    Health -= Damage;
}
