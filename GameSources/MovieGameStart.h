/*!
@file MovieGameStart.h
@brief �Q�[���J�n���̃��[�r�p
*/

#pragma once
#include "stdafx.h"
#include"Movie.h"

namespace basecross {
	class MovieGameStart :public Movie
	{
	private:
		int m_count;//���[�r�[�̐i�s�x
	public:
		MovieGameStart(shared_ptr<Stage>& stagePtr);
		~MovieGameStart();

		void OnCreate()override;
		void OnUpdate()override;

		void CameraChange()override;
	};

}
//end basecross
