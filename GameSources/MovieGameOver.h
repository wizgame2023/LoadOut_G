/*!
@file MovieGameOver.h
@brief �Q�[���N���A�̃��[�r�[
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieGameOver :public Movie
	{
	private:
		Vec3 m_tagetPos;//�ړI�n
		bool m_gameOverFlag;//�Q�[���I�[�o�[�̃t���O
	public:
		MovieGameOver(shared_ptr<Stage>& stagePtr);
		~MovieGameOver();

		void OnCreate()override;
		void OnUpdate()override;

	};


}
//end basecross
