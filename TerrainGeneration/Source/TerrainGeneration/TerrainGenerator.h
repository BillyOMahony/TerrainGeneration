// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TerrainGenerator.generated.h"

UCLASS()
class TERRAINGENERATION_API ATerrainGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Generation")
	TSubclassOf<class ATerrainChunk> TerrainChunk;

	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 ChunkSize = 32;

	// Offset in chunks of this chunk on the X axis
	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 ChunkOffsetX = 0;

	// Offset in chunks of this chunk on the Y axis
	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 ChunkOffsetY = 0;

	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 MaxHeight = 10;

	UPROPERTY(EditAnywhere, Category = "Generation")
	float ScaleBias = 0.125f;

	UPROPERTY(EditDefaultsOnly, Category = "Tile")
	TSubclassOf<AActor> Tile;

	// Tile XY dimensions (Tile should have equal len/width)
	UPROPERTY(EditAnywhere, Category = "Tile")
	float TileSizeXY = 100;

	// Tile Height
	UPROPERTY(EditAnywhere, Category = "Tile")
	float TileSizeZ = 20;
};
