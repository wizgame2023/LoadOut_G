/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"
#include "PillarEfect.h"

namespace basecross {
	class TrackingPillarEfect : public PillarEffect
	{
	private:

	public:
		TrackingPillarEfect(const shared_ptr<Stage>& stagePtr, Vec3 pos, wstring textureName, Vec2 velovity, int square = 36);
		~TrackingPillarEfect();

		virtual void OnUpdate() override;
	};

}
//end basecross
