// Shoot Them Up Game. All Rights Reserved


#include "Weapon/STUBaseWeapon.h"

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

