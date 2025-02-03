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
		weak_ptr<ViewBase> m_StageView;//�X�e�[�W�̃r���[(�Q�[���v���C�p)
		float m_mapSize;//�}�b�v�̃T�C�Y
		float m_speed;

	public:
		MovieGameStart(shared_ptr<Stage>& stagePtr,float mapSize,float speed = 50.0f);
		~MovieGameStart();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void CameraChange()override;
	};

}
//end basecross
