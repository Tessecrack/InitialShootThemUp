// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjecttile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class INITIALSHOOTTHEMUP_API ASTUProjecttile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUProjecttile();

	void SetShotDirection(const FVector &Direction)
    {
        ShotDirection = Direction;
    };

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

private: 
	FVector ShotDirection;
	
	AController *GetController() const;

};
