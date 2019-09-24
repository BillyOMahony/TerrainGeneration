// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"
#include "Engine/World.h"
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
	 *	@return ChunkOffset
	 */
	FVector2D GetChunkOffset();

	/**
	 *	Loads all tiles for this chunk into the world
	 */
	void LoadChunk(int32 ChunkSize, FVector2D ChunkOffset, int32 MaxHeight, float ScaleBias, float TileSizeXY, float TileSizeZ);

	/**
	 *	Unloads all tiles for this chunk from the world
	 */
	void UnloadChunk();

	/**
	 *	Called whenever a player enters this terrain chunk
	 */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 *	Called whenever a player leaves this terrain chunk
	 */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Tile")
	TSubclassOf<AActor> Tile;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent * PlayerOverlapCollider;

	ATerrainGenerator * TerrainGenerator;

	TArray<AActor *> Tiles;

	FVector2D ChunkOffset = FVector2D(0,0);
};

class FTileSpawnerTask : public FNonAbandonableTask 
{
	friend class FAutoDeleteAsyncTask<FTileSpawnerTask>;

public:
	FTileSpawnerTask(TArray<AActor *> Tiles, AActor* SpawningActor, TSubclassOf<AActor> NewTile, int32 NewChunkSize, float NewTileSizeXY, float NewTileSizeZ, float NewHeightStep, FFloatMatrixStruct NewHeightMatrix) :
		SpawnedTiles(Tiles),
		Spawner(SpawningActor),
		Tile(NewTile),
		ChunkSize(NewChunkSize),
		TileSizeXY(NewTileSizeXY),
		TileSizeZ(NewTileSizeZ),
		HeightStep(NewHeightStep),
		HeightMatrix(NewHeightMatrix)
	{}

protected:
	TArray<AActor*> SpawnedTiles;
	AActor* Spawner;
	TSubclassOf<AActor> Tile;
	int32 ChunkSize;
	float TileSizeXY;
	float TileSizeZ;
	float HeightStep;
	FFloatMatrixStruct HeightMatrix;

	void DoWork() {

		auto World = Spawner->GetWorld();

		for (int32 i = 0; i < HeightMatrix.GetLength(); i++)
		{
			for (int32 j = 0; j < HeightMatrix.GetWidth(); j++) {
				int32 Height = HeightMatrix.GetElementAt(i, j) / HeightStep;

				float XSpawnOffset = Spawner->GetActorLocation().X + (TileSizeXY * i) - ((ChunkSize * TileSizeXY) / 2) + (TileSizeXY / 2);
				float YSpawnOffset = Spawner->GetActorLocation().Y + (TileSizeXY * j) - ((ChunkSize * TileSizeXY) / 2) + (TileSizeXY / 2);
				float ZSpawnOffset = Spawner->GetActorLocation().Z + (TileSizeZ * Height);

				FVector SpawnLoc = FVector(XSpawnOffset, YSpawnOffset, ZSpawnOffset);
				FRotator SpawnRot = FRotator(0, 0, 0);
				if (!Tile) {
					UE_LOG(LogTemp, Error, TEXT("FTileSpawnerTask::DoWork() - No Tile Specified"));
					return;
				}
				if (!Spawner) {
					UE_LOG(LogTemp, Error, TEXT("No Spawner Assigned"));
					return;
				}

				AActor * SpawnedTile = World->SpawnActor<AActor>(Tile, SpawnLoc, SpawnRot);
				SpawnedTiles.Add(SpawnedTile);
				/*
				AActor * SpawnedTile = Spawner->GetWorld()->SpawnActor(Tile);
				SpawnedTile->SetActorLocation(SpawnLoc);
				
				*/
			}
		}
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTaskName, STATGROUP_ThreadPoolAsyncTasks);
	}
};
