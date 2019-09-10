// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataStructures.h"

/**
 * 
 */
class TERRAINGENERATION_API NoiseGenerator
{
public:
	NoiseGenerator();
	~NoiseGenerator();

	static FFloatMatrixStruct GenerateRandomNoiseMatrix(int32 X, int32 Y, int32 Seed = 1);

};
