// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainChunk.h"
#include "NoiseGenerator.h"
#include "TerrainGenerator.h"
#include "Components/BoxComponent.h"

// Sets default values
ATerrainChunk::ATerrainChunk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerOverlapCollider = CreateDefaultSubobject<UBoxComponent>(FName("Player Overlap Collider"));
	PlayerOverlapCollider->SetBoxExtent(FVector(50, 50, 50));
	PlayerOverlapCollider->SetCollisionProfileName("OverlapOnlyPawn");
	RootComponent = PlayerOverlapCollider;
}

void ATerrainChunk::SetTile(TSubclassOf<AActor> NewTile)
{
	Tile = NewTile;
}

void ATerrainChunk::SetTerrainGenerator(ATerrainGenerator * NewTerrainGenerator)
{
	TerrainGenerator = NewTerrainGenerator;
}

FVector2D ATerrainChunk::GetChunkOffset()
{
	return ChunkOffset;
}

void ATerrainChunk::LoadChunk(int32 ChunkSize, FVector2D NewChunkOffset, int32 MaxHeight, float ScaleBias, float TileSizeXY, float TileSizeZ)
{
	ChunkOffset = NewChunkOffset;

	PlayerOverlapCollider->SetRelativeScale3D(FVector(ChunkSize, ChunkSize, MaxHeight));
	PlayerOverlapCollider->OnComponentBeginOverlap.AddDynamic(this, &ATerrainChunk::OnOverlapBegin);
	PlayerOverlapCollider->OnComponentEndOverlap.AddDynamic(this, &ATerrainChunk::OnOverlapEnd);

	if (!Tile)
	{
		UE_LOG(LogTemp, Error, TEXT("TerrainGenerator::GenerateTerrainTiles() - Tile not assigned"));
		return;
	}
	FFloatMatrixStruct HeightMatrix = NoiseGenerator::GeneratePerlinNoiseMatrix(ChunkSize, ChunkSize, ChunkOffset.X * ChunkSize, ChunkOffset.Y * ChunkSize, ScaleBias);

	float HeightStep = 1.f / MaxHeight;

	for (int32 i = 0; i < HeightMatrix.GetLength(); i++)
	{
		for (int32 j = 0; j < HeightMatrix.GetWidth(); j++) {
			int32 Height = HeightMatrix.GetElementAt(i, j) / HeightStep;

			float XSpawnOffset = GetActorLocation().X + (TileSizeXY * i) - ((ChunkSize * TileSizeXY) / 2) + (TileSizeXY / 2);
			float YSpawnOffset = GetActorLocation().Y + (TileSizeXY * j) - ((ChunkSize * TileSizeXY) / 2) + (TileSizeXY / 2);
			float ZSpawnOffset = GetActorLocation().Z + (TileSizeZ * Height);

			FVector SpawnLoc = FVector(XSpawnOffset, YSpawnOffset, ZSpawnOffset);
			FRotator SpawnRot = FRotator(0, 0, 0);

			if (!Tile) {
				UE_LOG(LogTemp, Error, TEXT("FTileSpawnerTask::DoWork() - No Tile Specified"));
				return;
			}

			AActor * SpawnedTile = GetWorld()->SpawnActor<AActor>(Tile, SpawnLoc, SpawnRot);
			Tiles.Add(SpawnedTile);
		}
	}

	//(new FAutoDeleteAsyncTask<FTileSpawnerTask>(Tiles, this, Tile, ChunkSize, TileSizeXY, TileSizeZ, HeightStep, HeightMatrix))->StartBackgroundTask();
}

void ATerrainChunk::UnloadChunk()
{
	for (int32 i = 0; i < Tiles.Num(); i++) {
		Tiles[i]->Destroy();
	}
	Destroy();
}

void ATerrainChunk::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!TerrainGenerator) {
		UE_LOG(LogTemp, Error, TEXT("ATerrainChunk - TerrainGenerator not found"));
		return;
	}

	TerrainGenerator->OnPlayerEnterNewChunk(ChunkOffset);

}

void ATerrainChunk::OnOverlapEnd(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}
