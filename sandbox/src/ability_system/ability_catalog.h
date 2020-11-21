#pragma once

#include "ability.h"

namespace ralleon
{
	class AbilityCatalog
	{
	public:
		static void Init();
		static Ability* UnarmedAutoAttack();
	};
}