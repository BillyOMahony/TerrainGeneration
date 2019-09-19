// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseGenerator.h"
#include "PerlinNoise.h"

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

FFloatMatrixStruct NoiseGenerator::GeneratePerlinNoiseMatrix(int32 Width, int32 Height, int32 OffsetX, int32 OffsetY, int32 OctaveCount, float ScaleBias, int32 Seed)
{
	FFloatMatrixStruct PerlinNoise(Width, Height);
	UE_LOG(LogTemp, Error, TEXT("%i"), Width);
	UE_LOG(LogTemp, Error, TEXT("%i"), Height);
	UE_LOG(LogTemp, Error, TEXT("%i"), OffsetX);
	UE_LOG(LogTemp, Error, TEXT("%i"), OffsetY);
	UE_LOG(LogTemp, Error, TEXT("%f"), ScaleBias);

	for (int32 i = 0; i < Width; i++) {
		for (int32 j = 0; j < Height; j++) {
			float NoiseValue = PerlinNoise2D((OffsetX + i) * ScaleBias, (OffsetY + j) * ScaleBias);
			//UE_LOG(LogTemp, Error, TEXT("%f"), NoiseValue);
			PerlinNoise.SetElementAt(i, j, NoiseValue);
		}
	}

	return PerlinNoise;

	/*
	FFloatMatrixStruct RandomNoise = GenerateRandomNoiseMatrix(X, Y, Seed);
	FFloatMatrixStruct PerlinNoise(X, Y);

	for (int32 x = 0; x < RandomNoise.GetWidth(); x++) {
		for (int32 y = 0; y < RandomNoise.GetLength(); y++) {
			
			float Noise = 0.f;
			float Scale = 1.f;
			float ScaleAcc = 0.f;

			for (int o = 0; o < OctaveCount; o++) {
				int32 Pitch = X >> o;
				
				int32 SampleX1 = (x / Pitch) * Pitch;
				int32 SampleY1 = (y / Pitch) * Pitch;

				int32 SampleX2 = (SampleX1 + Pitch) % X;
				int32 SampleY2 = (SampleY1 + Pitch) % Y; // TODO Ensure Y should not be X

				float BlendX = (float)(x - SampleX1) / (float)Pitch;
				float BlendY = (float)(y - SampleY1) / (float)Pitch;

				float SampleT = (1.f - BlendX) * RandomNoise.GetElementAt(SampleX1, SampleY1) + BlendX * RandomNoise.GetElementAt(SampleX2, SampleY1);
				float SampleB = (1.f - BlendX) * RandomNoise.GetElementAt(SampleX1, SampleY2) + BlendX * RandomNoise.GetElementAt(SampleX2, SampleY2);

				Noise += (BlendY * (SampleB - SampleT) + SampleT) * Scale;
				ScaleAcc += Scale;
				Scale = Scale / ScaleBias;
			}

			PerlinNoise.SetElementAt(x, y, Noise / ScaleAcc);
		}
		
	}
	*/
	return PerlinNoise;
}

float NoiseGenerator::PerlinNoise2D(float x, float y)
{
	return PerlinAlgo::Noise(x, y, 0);
}
