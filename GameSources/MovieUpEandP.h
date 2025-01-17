/*!
@file Character.h
@brief �L�����N�^�[�Ȃ�
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MovieUpEandP :public Movie
	{
	private:
		float m_time;
		Col4 m_spriteCol;//�X�v���C�g(�Ó]�p)�̃J���[
		weak_ptr<Enemy> m_Enemy;//���[�r�[�̒����_�ƂȂ�Enemy
		weak_ptr<Player> m_Player;//���[�r�[�̒����_�ƂȂ�Player
		shared_ptr<Sprite> m_sprite;

	public:
		MovieUpEandP(shared_ptr<Stage>& stagePtr, weak_ptr<Enemy> enemy,weak_ptr<Player> player);
		~MovieUpEandP();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
