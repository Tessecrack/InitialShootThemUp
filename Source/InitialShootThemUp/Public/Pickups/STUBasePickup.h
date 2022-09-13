// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;

UCLASS()
class INITIALSHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickup();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

	virtual bool GivePickupTo(APawn *PlayerPawn);

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent *CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
    float RespawnTime = 5.0f;
	 
private: 
	float RotationYaw = 0.0f;
	void PickupWasTaken();
	void Respawn();

	void GenerateRotationYaw();
};
