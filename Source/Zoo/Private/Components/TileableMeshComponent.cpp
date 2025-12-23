// Copyright Epic Games, Inc. All Rights Reserved.

#include "Components/TileableMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Engine.h"

UTileableMeshComponent::UTileableMeshComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

UTileableMeshComponent::~UTileableMeshComponent()
{
	ClearSegments();
}

void UTileableMeshComponent::BeginPlay()
{
	Super::BeginPlay();
	RebuildMesh();
}

#if WITH_EDITOR
void UTileableMeshComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if (PropertyChangedEvent.Property && 
		(PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTileableMeshComponent, SegmentCount) ||
		 PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTileableMeshComponent, HeightAxis) ||
		 PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTileableMeshComponent, SegmentMesh) ||
		 PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTileableMeshComponent, AttachComponent) ||
		 PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UTileableMeshComponent, AnchorComponent)))
	{
		if (IsRegistered())
		{
			RebuildMesh();
		}
	}
}
#endif

void UTileableMeshComponent::RebuildMesh()
{
	if (!IsRegistered())
	{
		return;
	}

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	// Get or create attach component
	USceneComponent* AttachTo = GetOrCreateAttachComponent();
	if (!AttachTo)
	{
		ClearSegments();
		return;
	}

	// Clear existing segments
	ClearSegments();

	// Check if mesh is valid
	if (!SegmentMesh)
	{
		return;
	}

	// Get mesh bounds to calculate spacing
	FBoxSphereBounds MeshBounds = SegmentMesh->GetBounds();
	FVector BoxExtent = MeshBounds.BoxExtent; // BoxExtent is already half-extents
	
	const float SegmentLength = GetAxisExtent(BoxExtent, HeightAxis) * 2.0f;
	const float BaseOffset = GetAxisOffset(BoxExtent, HeightAxis);

	if (SegmentLength <= KINDA_SMALL_NUMBER)
	{
		return;
	}

	// Create StaticMeshComponents for each segment
	SegmentComponents.Reserve(SegmentCount);

	for (int32 i = 0; i < SegmentCount; ++i)
	{
		// Create new StaticMeshComponent
		UStaticMeshComponent* NewSegment = NewObject<UStaticMeshComponent>(
			Owner,
			UStaticMeshComponent::StaticClass(),
			*FString::Printf(TEXT("Segment_%d"), i)
		);

		// Configure the component
		NewSegment->SetStaticMesh(SegmentMesh);
		NewSegment->SetupAttachment(AttachTo);
		NewSegment->SetMobility(EComponentMobility::Movable);
		NewSegment->SetVisibility(true);
		NewSegment->SetHiddenInGame(false);

		// Calculate position for this segment
		const float LocationValue = BaseOffset + (i * SegmentLength);
		FVector Location = MakeLocationForAxis(HeightAxis, LocationValue);
		NewSegment->SetRelativeLocation(Location);

		// Register the component
		NewSegment->RegisterComponent();

		// Add to array
		SegmentComponents.Add(NewSegment);
	}

	// Calculate final height/extent
	const float FinalExtent = SegmentCount * SegmentLength;

	// Update anchor component position if set
	if (AnchorComponent)
	{
		FVector AnchorLocation = MakeLocationForAxis(HeightAxis, FinalExtent);
		AnchorComponent->SetRelativeLocation(AnchorLocation);
	}
}

void UTileableMeshComponent::ClearSegments()
{
	for (UStaticMeshComponent* Segment : SegmentComponents)
	{
		if (IsValid(Segment))
		{
			Segment->DestroyComponent();
		}
	}
	SegmentComponents.Empty();
}

USceneComponent* UTileableMeshComponent::GetOrCreateAttachComponent()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return nullptr;
	}

	// Use provided AttachComponent if set
	if (AttachComponent && IsValid(AttachComponent))
	{
		return AttachComponent;
	}

	// Otherwise use root component
	return Owner->GetRootComponent();
}

float UTileableMeshComponent::GetAxisExtent(const FVector& BoxExtent, EAxis::Type Axis) const
{
	switch (Axis)
	{
		case EAxis::X: return BoxExtent.X;
		case EAxis::Y: return BoxExtent.Y;
		case EAxis::Z: return BoxExtent.Z;
		default: return BoxExtent.Z;
	}
}

float UTileableMeshComponent::GetAxisOffset(const FVector& BoxExtent, EAxis::Type Axis) const
{
	switch (Axis)
	{
		case EAxis::X: return -BoxExtent.X;
		case EAxis::Y: return -BoxExtent.Y;
		case EAxis::Z: return -BoxExtent.Z;
		default: return -BoxExtent.Z;
	}
}

FVector UTileableMeshComponent::MakeLocationForAxis(EAxis::Type Axis, float Value) const
{
	switch (Axis)
	{
		case EAxis::X: return FVector(Value, 0.0f, 0.0f);
		case EAxis::Y: return FVector(0.0f, Value, 0.0f);
		case EAxis::Z: return FVector(0.0f, 0.0f, Value);
		default: return FVector(0.0f, 0.0f, Value);
	}
}
