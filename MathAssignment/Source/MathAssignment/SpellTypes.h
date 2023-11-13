#pragma once

UENUM(BlueprintType, Meta = (Bitflags))
enum class ESpellTypes 
{
	Ranged, 
	Melee,
	Instant,
	AutoAttack,
	Attacking,
	Cooldown
};