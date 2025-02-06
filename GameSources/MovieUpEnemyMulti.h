/*!
@file MovieUpEnemyMulti.h
@brief �G�������ł������郀�[�r�[
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieUpEnemyMulti :public Movie
	{
	private:
		Vec3 m_tagetPos;//�ړI�n
		Vec3 m_movieCameraAt;//�J�����̒����_

		vector<weak_ptr<Enemy>> m_upEnemyVec;//�ł��グ��G�̃|�C���^�̔z��
		vector<float> m_upEnemyMoveAngleVec;//�ł�������G���ǂ̕����ɑł�������̂��ۑ�����z��

		bool m_removeFlag;//���[�r�[���I������t���O
	public:
		MovieUpEnemyMulti(shared_ptr<Stage>& stagePtr,vector<weak_ptr<Enemy>> enemyVec);
		~MovieUpEnemyMulti();

		void OnCreate()override;
		void OnUpdate()override;

	};
}
//end basecross
