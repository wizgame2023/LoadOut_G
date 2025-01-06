/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross{

	class NuberManager :public GameObject
	{
		int m_number;
		bool m_numLength;//1���ɂ��邩2���ɂ��邩

		Vec3 m_pos;
		Vec2 m_scale;

		shared_ptr<SpriteNum> m_spriteOne;//��̈�
		shared_ptr<SpriteNum> m_spriteTen;//�\�̈�

	public:
		NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos, bool numLength);
		NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos);
		~NuberManager();

		void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V

		void SetNum(int number);//�Z�b�^�[

	};

}
//end basecross

