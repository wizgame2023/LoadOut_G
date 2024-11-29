/*!
@file MovieUpPlayer.h
@brief �}���z�[���ɓ������đł�������v���C���[
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieUpPlayer :public Movie
	{
	private:
		float m_time;
		Col4 m_spriteCol;//�X�v���C�g(�Ó]�p)�̃J���[
		shared_ptr<Sprite> m_sprite;
	public:
		MovieUpPlayer(shared_ptr<Stage>& stagePtr);
		~MovieUpPlayer();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
