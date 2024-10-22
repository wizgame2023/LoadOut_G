/*!
@file Player.h
@brief ƒvƒŒƒCƒ„[‚È‚Ç
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player :GameObject
	{
	public:
		Player(const shared_ptr<Stage>& StagePtr);
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}
//end basecross

