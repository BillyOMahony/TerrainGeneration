// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainChunk.h"
#include "DataStructures.h"
#include "NoiseGenerator.h"
#include "Components/BoxComponent.h"

// Sets default values
ATerrainChunk::ATerrainChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerOverlapCollider = CreateDefaultSubobject<UBoxComponent>(FName("Player Overlap Collider"));
	PlayerOverlapCollider->SetBoxExtent(FVector(50, 50, 50));
}

void ATerrainChunk::SetTile(TSubclassOf<AActor> NewTile)
{
	Tile = NewTile;
}

void ATerrainChunk::SetTerrainGenerator(ATerrainGenerator * NewTerrainGenerator)
{
	TerrainGenerator = NewTerrainGenerator;
}

void ATerrainChunk::LoadChunk(int32 ChunkSize, FVector2D ChunkOffset, int32 MaxHeight, float ScaleBias, float TileSizeXY, float TileSizeZ)
{
	PlayerOverlapCollider->SetRelativeScale3D(FVector(ChunkSize, ChunkSize, MaxHeight));

	if (!Tile)
	{
		UE_LOG(LogTemp, Error, TEXT("TerrainGenerator::GenerateTerrainTiles() - Tile not assigned"));
		return;
	}
	auto HeightMatrix = NoiseGenerator::GeneratePerlinNoiseMatrix(ChunkSize, ChunkSize, ChunkOffset.X * ChunkSize, ChunkOffset.Y * ChunkSize, ScaleBias);
	float HeightStep = 1.f / MaxHeight;
	for (int32 i = 0; i < HeightMatrix.GetLength(); i++)
	{
		for (int32 j = 0; j < HeightMatrix.GetWidth(); j++) {
			int32 Height = HeightMatrix.GetElementAt(i, j) / HeightStep;

			float XSpawnOffset = GetActorLocation().X + (TileSizeXY * i) - ((ChunkSize * TileSizeXY) / 2) +(TileSizeXY / 2);
			float YSpawnOffset = GetActorLocation().Y + (TileSizeXY * j) - ((ChunkSize * TileSizeXY) / 2) +(TileSizeXY / 2);
			float ZSpawnOffset = GetActorLocation().Z + (TileSizeZ * Height);

			FVector SpawnLoc = FVector(XSpawnOffset, YSpawnOffset, ZSpawnOffset);

			AActor * SpawnedTile = GetWorld()->SpawnActor<AActor>(Tile, SpawnLoc, GetActorRotation());
			Tiles.Add(SpawnedTile);
		}
	}
}

void ATerrainChunk::UnloadChunk()
{

}
