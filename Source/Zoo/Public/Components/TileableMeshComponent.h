// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "TileableMeshComponent.generated.h"

/**
 * Component that builds a tiled mesh by stacking mesh segments without distortion.
 * Creates StaticMeshComponents dynamically based on SegmentCount.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZOO_API UTileableMeshComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTileableMeshComponent(const FObjectInitializer& ObjectInitializer);
	virtual ~UTileableMeshComponent();

	/** Number of segments to stack */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tileable Mesh Settings", meta = (ClampMin = "1"))
	int32 SegmentCount = 1;

	/** Which axis represents the height/extent of the segment (X, Y, or Z) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tileable Mesh Settings")
	TEnumAsByte<EAxis::Type> HeightAxis = EAxis::Z;

	/** The StaticMesh asset to use for segments */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tileable Mesh Settings")
	TObjectPtr<UStaticMesh> SegmentMesh;

	/** The SceneComponent to attach segments to (if null, creates one) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tileable Mesh Settings")
	TObjectPtr<USceneComponent> AttachComponent;

	/** The SceneComponent to position at the top (optional) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tileable Mesh Settings")
	TObjectPtr<USceneComponent> AnchorComponent;

	/** Rebuilds the tiled mesh segments */
	UFUNCTION(BlueprintCallable, Category = "Tileable Mesh")
	void RebuildMesh();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:	
	/** Array of created StaticMeshComponents */
	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> SegmentComponents;

	/** Gets the extent value for the specified axis */
	float GetAxisExtent(const FVector& BoxExtent, EAxis::Type Axis) const;

	/** Gets the offset value for the specified axis */
	float GetAxisOffset(const FVector& BoxExtent, EAxis::Type Axis) const;

	/** Creates a location vector with value on the specified axis */
	FVector MakeLocationForAxis(EAxis::Type Axis, float Value) const;

	/** Clears all created segment components */
	void ClearSegments();

	/** Ensures AttachComponent exists */
	USceneComponent* GetOrCreateAttachComponent();
};
