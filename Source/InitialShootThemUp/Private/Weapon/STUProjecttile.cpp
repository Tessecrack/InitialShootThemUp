// Shoot Them Up Game. All Rights Reserved


#include "Weapon/STUProjecttile.h"

// Sets default values
ASTUProjecttile::ASTUProjecttile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTUProjecttile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUProjecttile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

