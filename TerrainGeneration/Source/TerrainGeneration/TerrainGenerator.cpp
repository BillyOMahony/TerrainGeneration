// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGenerator.h"
#include "NoiseGenerator.h"
#include "TerrainChunk.h"
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

	GenerateInitialChunks();
}

void ATerrainGenerator::OnPlayerEnterNewChunk(FVector2D ChunkOffset)
{
	UE_LOG(LogTemp, Warning, TEXT("ATerrainGenerator::OnPlayerEnterNewChunk EnteredChunk: (%f, %f)"), ChunkOffset.X, ChunkOffset.Y);

	int32 x = static_cast<int32>(FMath::RoundHalfFromZero(ChunkOffset.X)) - 1;
	int32 y = static_cast<int32>(FMath::RoundHalfFromZero(ChunkOffset.Y)) - 1;

	TArray<ATerrainChunk *> NewChunks;

	for (int32 i = x; i < x + 3; i++) {
		for (int32 j = y; j < y + 3; j++) {
			bool ChunkFound = false;
			for (int32 k = 0; k < LoadedChunks.Num(); k++) {
				if (LoadedChunks[k]->GetChunkOffset().Equals(FVector2D(i, j))) {
					NewChunks.Add(LoadedChunks[k]);
					LoadedChunks.RemoveAt(k);
					// Chunk already loaded so break
					ChunkFound = true;
					break;
				}
			}
			if (!ChunkFound) {
				// If no chunk already exists, load it.
				UE_LOG(LogTemp, Warning, TEXT("ATerrainGenerator::OnPlayerEnterNewChunk Adding Chunk: (%i, %i)"), i, j);
				NewChunks.Add(CreateChunk(FVector2D(i, j)));
			}
		}
	}

	for (int32 i = 0; i < LoadedChunks.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("ATerrainGenerator::OnPlayerEnterNewChunk Removing Chunk: (%f, %f)"), LoadedChunks[i]->GetChunkOffset().X, LoadedChunks[i]->GetChunkOffset().Y);
		LoadedChunks[i]->UnloadChunk();
	}

	LoadedChunks = NewChunks;
}

void ATerrainGenerator::GenerateInitialChunks()
{
	LoadedChunks.Add(CreateChunk(FVector2D(-1, -1)));
	LoadedChunks.Add(CreateChunk(FVector2D(-1, 0)));
	LoadedChunks.Add(CreateChunk(FVector2D(-1, 1)));
	LoadedChunks.Add(CreateChunk(FVector2D(0, -1)));
	LoadedChunks.Add(CreateChunk(FVector2D(0, 0)));
	LoadedChunks.Add(CreateChunk(FVector2D(0, 1)));
	LoadedChunks.Add(CreateChunk(FVector2D(1, -1)));
	LoadedChunks.Add(CreateChunk(FVector2D(1, 0)));
	LoadedChunks.Add(CreateChunk(FVector2D(1, 1)));
}

ATerrainChunk * ATerrainGenerator::CreateChunk(FVector2D ChunkOffset)
{
	// Load Initial Chunk
	if (!TerrainChunk) {
		UE_LOG(LogTemp, Error, TEXT("ATerrainGenerator - TerrainChunk Not Found"));
		return nullptr;
	};

	FVector SpawnOffset = FVector(ChunkOffset.X * TileSizeXY * ChunkSize, ChunkOffset.Y * TileSizeXY * ChunkSize, 0);

	ATerrainChunk * Chunk = GetWorld()->SpawnActor<ATerrainChunk>(TerrainChunk, SpawnOffset, GetActorRotation());
	Chunk->SetTile(Tile);
	Chunk->SetTerrainGenerator(this);
	Chunk->LoadChunk(ChunkSize, ChunkOffset, MaxHeight, ScaleBias, TileSizeXY, TileSizeZ);
	return Chunk;
}

