// Shoot Them Up Game. All Rights Reserved


#include "Components/STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const 
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter *Character = Cast<ASTUBaseCharacter>(GetPawnOwner());

    return Character && Character->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}