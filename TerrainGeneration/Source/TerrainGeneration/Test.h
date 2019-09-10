// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataStructures.h"
#include "Test.generated.h"

UCLASS()
class TERRAINGENERATION_API ATest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	FFloatMatrixStruct MatrixTest;

private:
	UPROPERTY(EditAnywhere)
	int32 X = 32;

	UPROPERTY(EditAnywhere)
	int32 Y = 32;
};
