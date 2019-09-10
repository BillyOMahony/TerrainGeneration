// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseGenerator.h"

NoiseGenerator::NoiseGenerator()
{
}

NoiseGenerator::~NoiseGenerator()
{
}

FFloatMatrixStruct NoiseGenerator::GenerateRandomNoiseMatrix(int32 X, int32 Y, int32 Seed)
{
	FRandomStream Stream(Seed);

	FFloatMatrixStruct FloatMatrix =  FFloatMatrixStruct(X, Y);
	for (int32 i = 0; i < X; i++) {
		for (int32 j = 0; j < Y; j++) {
			FloatMatrix.SetElementAt(i, j, Stream.FRandRange(0, 1));
		}
	}
	return FloatMatrix;
}
