// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainChunk.generated.h"

UCLASS()
class TERRAINGENERATION_API ATerrainChunk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainChunk();

	/**
	 *	@param NewTile - Tile actor to spawn in
 	 */
	void SetTile(TSubclassOf<AActor> NewTile);

	/**
	 *	@param NewTerrainGenerator - The TerrainGenerator Actor to use
	 */
	void SetTerrainGenerator(class ATerrainGenerator * NewTerrainGenerator);

	/**
	 *	Loads all tiles for this chunk into the world
	 */
	void LoadChunk(int32 ChunkSize, FVector2D ChunkOffset, int32 MaxHeight, float ScaleBias, float TileSizeXY, float TileSizeZ);

	/**
	 *	Unloads all tiles for this chunk from the world
	 */
	void UnloadChunk();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Tile")
	TSubclassOf<AActor> Tile;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * PlayerOverlapCollider;

	ATerrainGenerator * TerrainGenerator;

	TArray<AActor *> Tiles;


};
