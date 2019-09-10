// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core.h"
#include "Engine.h"
#include "DataStructures.generated.h"

USTRUCT(BlueprintType)
struct FFloatVectorStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> FloatVector;

	FFloatVectorStruct() {
		FloatVector.Init(0, 1);
	}

	FFloatVectorStruct(int32 length) {
		if (length > 0) {
			FloatVector.Init(0, length);
		}
		else {
			FloatVector.Init(0, 1);
		}
	}

	float Get(int32 Element) {
		return FloatVector[Element];
	}

	void Set(int32 Element, float Value) {
		FloatVector[Element] = Value;
	}

};

USTRUCT(BlueprintType)
struct FFloatMatrixStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFloatVectorStruct> Columns; //Consider this array the x axis, and the contents of the Columns it's y axis

private:
	int32 X;
	int32 Y;

public:
	// Default contructor creates a 1x1 matrix
	FFloatMatrixStruct() {
		FFloatVectorStruct NewStruct = FFloatVectorStruct();
		Columns.Add(NewStruct);
	}

	FFloatMatrixStruct(int32 newX, int32 newY) {
		X = newX;
		Y = newY;
		for (int32 i = 0; i < newX; i++) {
			FFloatVectorStruct NewStruct = FFloatVectorStruct(newY);
			Columns.Add(NewStruct);
		}
	}

	float GetElementAt(int32 x, int32 y) {
		if (X > x && Y > y) {
			return Columns[x].Get(y);
		}
	}

	void SetElementAt(int32 x, int32 y, float value) {
		if (X > x && Y > y) {
			Columns[x].Set(y, value);
		}
	}

	void PrintMatrix() {
		for (int32 i = 0; i < X; i++) {
			FString string = "";
			for (int32 j = 0; j < Y; j++) {
				string.Append(FString::SanitizeFloat(Columns[i].Get(j)));
				string.Append(", ");
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
		}
	}
};