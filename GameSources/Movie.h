/*!
@file Character.h
@brief ���[�r�[�֌W�̐e�N���X
*/

#pragma once
#include "stdafx.h"
#include "MyCamera.h"
#include "StageCollisionManager.h"
#include "StageManager.h"

namespace basecross {
	class Movie :public GameObject
	{
	private:
		vector<weak_ptr<Actor>> m_actorVec;//�����I�u�W�F�N�g������z��
		vector<weak_ptr<Spanner>> m_batteryVec;//�o�b�e���[������z��
		vector<weak_ptr<Manhole>> m_manholeVec;//�}���z�[��������z��
		vector<weak_ptr<Sprite>> m_spriteVec;//�X�v���C�g��������z��
	protected:
		shared_ptr<MyCamera> m_stageCamera;//�X�e�[�W�p�̃J����
		shared_ptr<Camera> m_movieCamera;//���[�r�[�p�̂��߂�
		shared_ptr<StageCollisionManager> m_collsionManager;//�R���W�����}�l�[�W���[
		shared_ptr<StageManager> m_stageManager;//�X�e�[�W�}�l�[�W���[
		int m_count;
	public:
		Movie(shared_ptr<Stage>& stagePtr);
		~Movie();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		virtual void OnDestroy()override;

		//���[�r�[�p�̃J�����ɕύX������
		virtual void CameraChange();

		//�J������ړI�n�Ɍ����Ĉړ�������
		virtual Vec3 CameraMove(float speed,Vec3 pos,Vec3 tagetPos);
	};

}
//end basecross
