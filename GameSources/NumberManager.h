/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class NuberManager :public GameObject
	{
		int m_number;
		bool m_numLength;//1桁にするか2桁にするか

		Vec3 m_pos;
		Vec2 m_scale;

		shared_ptr<SpriteNum> m_spriteOne;//一の位
		shared_ptr<SpriteNum> m_spriteTen;//十の位

	public:
		NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos, bool numLength);
		NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos);
		~NuberManager();

		void OnCreate()override;//作成
		void OnUpdate()override;//更新

		void SetNum(int number);//セッター

	};

}
//end basecross

