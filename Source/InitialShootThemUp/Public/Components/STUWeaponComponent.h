// Shoot Them Up Game. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INITIALSHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();

	void StartFire();
    void StopFire();
    void NextWeapon();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
    UAnimMontage *EquipAnimMontage;

private: 
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
    TArray<ASTUBaseWeapon *> Weapons;

	int32 CurrentWeaponIndex = 0;

	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUBaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
    void EquipWeapon(int32 WeaponIndex);

	void PlayAnimMontage(UAnimMontage *Animation);

	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
};
