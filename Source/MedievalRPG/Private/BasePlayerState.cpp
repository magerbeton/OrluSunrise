// All Copyright belongs to Konstantin Passig


#include "BasePlayerState.h"

#include "LevelComponent.h"

void ABasePlayerState::AddXpToSkill_Implementation(EXpTypeEnum XpType, float XpAmount)
{
	if(Levels->IsValidLowLevel())
	{
		Levels->AddXpToSkill(XpType,XpAmount);
	}
}

