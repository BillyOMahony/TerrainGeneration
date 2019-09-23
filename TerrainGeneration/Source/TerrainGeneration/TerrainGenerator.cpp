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

	if (!TerrainChunk) return;

	ATerrainChunk * Chunk00 = GetWorld()->SpawnActor<ATerrainChunk>(TerrainChunk, GetActorLocation(), GetActorRotation());
	Chunk00->SetTile(Tile);
	Chunk00->LoadChunk(ChunkSize, FVector2D(ChunkOffsetX, ChunkOffsetY), MaxHeight, ScaleBias, TileSizeXY, TileSizeZ);

	FVector Offset = FVector((ChunkOffsetX + TileSizeXY) * ChunkSize, 0, 0);
	ATerrainChunk * Chunk11 = GetWorld()->SpawnActor<ATerrainChunk>(TerrainChunk, GetActorLocation() + Offset, GetActorRotation());
	Chunk11->SetTile(Tile);
	Chunk11->LoadChunk(ChunkSize, FVector2D(1, ChunkOffsetY), MaxHeight, ScaleBias, TileSizeXY, TileSizeZ);

}

