/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class happysky : public GameObject
	{
	public : 
		static const std::map<std::wstring, Vec3> pairs;

	private :
		std::vector<std::shared_ptr<GameObject>> m_skybase;

	public :
		happysky(const shared_ptr<Stage>& stage)
			: GameObject(stage)
		{
		}

		void OnCreate() override;
		void OnUpdate() override;
		void OnDraw() override;
	};
}
//end basecross
