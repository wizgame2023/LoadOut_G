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
		weak_ptr<Actor> m_actor;
	public:
		TrackingPillarEfect(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> m_actor, Vec3 pos, wstring textureName, Vec2 velovity, int square = 36);
		~TrackingPillarEfect();

		virtual void OnUpdate() override;
	};

}
//end basecross
