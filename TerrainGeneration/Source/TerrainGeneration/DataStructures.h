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

	float GetMin() {
		float min = FloatVector[0];
		for (int32 i = 1; i < FloatVector.Num(); i++) {
			if (FloatVector[i] < min) {
				min = FloatVector[i];
			}
		}
		return min;
	}

	float GetMax() {
		float max = FloatVector[0];
		for (int32 i = 1; i < FloatVector.Num(); i++) {
			if (FloatVector[i] > max) {
				max = FloatVector[i];
			}
		}
		return max;
	}

	float GetElementAt(int32 Element) {
		return FloatVector[Element];
	}

	void SetElementAt(int32 Element, float Value) {
		FloatVector[Element] = Value;
	}

};

USTRUCT(BlueprintType)
struct FFloatMatrixStruct {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FFloatVectorStruct> Rows; //Consider this array the y axis, and the contents of the Rows it's x axis

private:
	int32 X;
	int32 Y;

public:
	// Default contructor creates a 1x1 matrix
	FFloatMatrixStruct() {
		FFloatVectorStruct NewStruct = FFloatVectorStruct();
		Rows.Add(NewStruct);
	}

	FFloatMatrixStruct(int32 newX, int32 newY) {
		X = newX;
		Y = newY;
		for (int32 i = 0; i < newX; i++) {
			FFloatVectorStruct NewStruct = FFloatVectorStruct(newY);
			Rows.Add(NewStruct);
		}
	}

	/**
	 *	Returns the element at [x,y].
	 *	If the element cannot be found, -1 is returned indicating something went wrong.
	 */
	float GetElementAt(int32 x, int32 y) {
		if (X > x && Y > y) {
			return Rows[x].GetElementAt(y);
		}
		return -1; // Something has gone wrong
	}

	void SetElementAt(int32 x, int32 y, float value) {
		if (X > x && Y > y) {
			Rows[x].SetElementAt(y, value);
		}
	}

	void PrintMatrix() {
		for (int32 i = 0; i < X; i++) {
			FString string = "";
			for (int32 j = 0; j < Y; j++) {
				string.Append(FString::SanitizeFloat(Rows[i].GetElementAt(j)));
				string.Append(", ");
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *string);
		}
	}

	float GetMin() {
		float min = Rows[0].GetMin();
		for (int32 i = 1; i < X; i++) {
			if (Rows[i].GetMin() < min) {
				min = Rows[i].GetMin();
			}
		}
		return min;
	}

	float GetMax() {
		float max = Rows[0].GetMax();
		for (int32 i = 1; i < X; i++) {
			if (Rows[i].GetMax() > max) {
				max = Rows[i].GetMax();
			}
		}
		return max;
	}

	int32 GetWidth()
	{
		return X;
	}

	int32 GetLength()
	{
		return Y;
	}
};