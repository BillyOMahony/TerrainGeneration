// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"
#include "TerrainGenerator.generated.h"

UCLASS()
class TERRAINGENERATION_API ATerrainGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATerrainGenerator();

	/**
	 * Sets Grid Size, used for X and Y Axis
	 */
	void SetGridSize(int32 NewGridSize);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 *	Spawns tiles according to the parameters
	 */
	void GenerateTerrainTiles();

	/**
	 * Gets a Matrix which is used in generation of the terrain
	 * @return A matrix to be used in terrain generation
	 */
	FFloatMatrixStruct GetTerrainMatrix();

private:
	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 GridSize = 32;

	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 MaxHeight = 10;

	UPROPERTY(EditAnywhere, Category = "Generation")
	int32 Seed = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Tile")
	TSubclassOf<AActor> Tile;

	// Tile XY dimensions (Tile should have equal len/width)
	UPROPERTY(EditAnywhere, Category = "Tile")
	float TileSizeXY = 100;

	// Tile Height
	UPROPERTY(EditAnywhere, Category = "Tile")
	float TileSizeZ = 20;



};
