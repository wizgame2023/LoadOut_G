/*!
@file Manhole.h
@brief �}���z�[��
*/

#pragma once
#include "stdafx.h"
#include "ClearObject.h"
#include "WaterPillar.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		weak_ptr<MapManager> m_mapManager;//�}�b�v�}�l�[�W���[

		shared_ptr<ClearObject> m_clearObject;//�����ȕ�
		shared_ptr<WaterPillar> m_waterPillar;//����

		int m_charen;//�i�s�x

		float m_coolTime;//���Ԃ𑪂邽�߂ɕK�v
		float m_stanbyTime;//���Ԃ𑪂邽�߂ɕK�v
		float m_blinkingTime;//�_�ł��鎞�Ԃ𑪂�

		bool m_playerStanbyFlag;//�v���C���[�����ނ��܂t���O

	public:
		//�}���z�[���̏�ԑJ��
		enum STATE
		{
			Manhole_None,
			Manhole_Start,
			Manhole_SoonUp,
			Manhole_Up,
			Manhole_Used
		};

		Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos);
		~Manhole();

		void OnCreate()override;
		void OnUpdate()override;

		void ManholeTransition();

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;//�����������ɏ���
		void OnCollisionExit(shared_ptr<GameObject>& other)override;//���ꂽ�Ƃ��ɏ���

		int GetState();//�Q�b�^�[
	};

}
//end basecross
