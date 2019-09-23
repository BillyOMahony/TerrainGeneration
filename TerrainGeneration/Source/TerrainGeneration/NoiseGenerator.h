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

	/**
	 *	Generates a matrix of random values between 0 and 1
	 *	@param X Width of the matrix
	 *	@param Y Height of the matrix
	 *	@param Seed Seed used by the random number generator
	 *	@return A matrix containing the random values
	 */
	static FFloatMatrixStruct GenerateRandomNoiseMatrix(int32 X, int32 Y, int32 Seed = 1);

	/**
	 *	Generates a matrix of perlin noise values between 0 and 1
	 *	@param Width Width of the matrix
	 *	@param Height Height of the matrix
	 *	@param OffsetX Offset in tiles of this chunk from origin on the X axis
	 *	@param OffsetY Offset in tiles of this chunk from origin on the Y axis
	 *  @param OctaveCount TODO
	 *	@param ScaleBias TODO
	 *	@param Seed Seed used by the random number generator
	 */
	static FFloatMatrixStruct GeneratePerlinNoiseMatrix(int32 Width, int32 Height, int32 OffsetX, int32 OffsetY, float ScaleBias = 1.f);

	/**
	 *
	 */
	static float PerlinNoise2D(float x, float y);
};
