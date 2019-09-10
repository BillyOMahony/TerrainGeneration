// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGenerator.h"
#include "NoiseGenerator.h"
#include "Engine/World.h"

// Sets default values
ATerrainGenerator::ATerrainGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATerrainGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateTerrainTiles();
}

FFloatMatrixStruct ATerrainGenerator::GetTerrainMatrix()
{
	return NoiseGenerator::GenerateRandomNoiseMatrix(GridSize, GridSize, Seed);
}

void ATerrainGenerator::GenerateTerrainTiles()
{
	if(!Tile)
	{
		UE_LOG(LogTemp, Error, TEXT("TerrainGenerator::GenerateTerrainTiles() - Tile not assigned"));
		return;
	}
	auto HeightMatrix = GetTerrainMatrix();
	float HeightStep = 1.f / MaxHeight;
	UE_LOG(LogTemp, Warning, TEXT("fhajk"));
	for(int32 i = 0; i < HeightMatrix.GetLength(); i++)
	{
		for (int32 j = 0; j < HeightMatrix.GetWidth(); j++){
			int32 Height = HeightMatrix.GetElementAt(i, j)/HeightStep;

			UE_LOG(LogTemp, Warning, TEXT("%f Rounded to %i"), HeightMatrix.GetElementAt(i, j), Height);

			float XSpawnOffset = GetActorLocation().X + (TileSizeXY * i);
			float YSpawnOffset = GetActorLocation().Y + (TileSizeXY * j);
			float ZSpawnOffset = GetActorLocation().Z + (TileSizeZ * Height);

			FVector SpawnLoc = FVector(XSpawnOffset, YSpawnOffset, ZSpawnOffset);

			GetWorld()->SpawnActor<AActor>(Tile, SpawnLoc, GetActorRotation());

		}
	}

}

void ATerrainGenerator::SetGridSize(int32 NewGridSize)
{
	GridSize = NewGridSize;
}
