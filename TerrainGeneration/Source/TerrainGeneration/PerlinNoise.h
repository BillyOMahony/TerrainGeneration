// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * TODO Document
 * http://mrl.nyu.edu/~perlin/noise/
 */
static class TERRAINGENERATION_API PerlinAlgo
{
public:
	/**
	 *	Fade function used to generate Perlin Noise
	 *	Interpolates the smoothing along an S-Shaped curve
	 */
	static FORCEINLINE float Fade(float t);

	/**
	 *	Returns the gradient value for a given integer
	 */
	static FORCEINLINE float Grad(int32 hash, float x, float y, float z);

	/**
	 *	TODO
	 */
	static FORCEINLINE float Lerp(float x, float a, float b);

	/**
	 *	TODO
	 */
	static float Noise(float x, float y, float z);

};
