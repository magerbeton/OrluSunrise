// All Copyright belongs to Konstantin Passig


#include "CusomNavigationInvokerComponent.h"

void UCusomNavigationInvokerComponent::SetTileGenerationRadius(float Radius)
{
	TileGenerationRadius = Radius;
}

float UCusomNavigationInvokerComponent::GetTileGenerationRadius()
{
	return TileGenerationRadius;
}

void UCusomNavigationInvokerComponent::SetTileRemovalRadius(float Radius)
{
	TileRemovalRadius = Radius;
}

float UCusomNavigationInvokerComponent::GetTileRemovalRadius()
{
	return TileRemovalRadius;
}
