/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class NuberManager :public GameObject
	{
		int m_nuber;

		Vec3 m_pos;
		Vec2 m_scale;

		shared_ptr<SpriteNum> m_sprite;

	public:
		NuberManager(shared_ptr<Stage>& stage,int nuber,Vec2 scale,Vec3 pos);
		~NuberManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

	};

}
//end basecross

