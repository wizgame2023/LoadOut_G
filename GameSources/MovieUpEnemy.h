/*!
@file MovieUpEnemy.h
@brief �G���オ�郀�[�r�[
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class MovieUpEnemy :public Movie
	{
	private:
		float m_time;
		Col4 m_spriteCol;//�X�v���C�g(�Ó]�p)�̃J���[
		weak_ptr<Enemy> m_Enemy;//���[�r�[�̒����_�ƂȂ�Enemy
		shared_ptr<Sprite> m_sprite;
	public:
		MovieUpEnemy(shared_ptr<Stage>& stagePtr,weak_ptr<Enemy> enemy);
		~MovieUpEnemy();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
