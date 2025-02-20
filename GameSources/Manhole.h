/*!
@file Manhole.h
@brief �}���z�[��
*/

#pragma once
#include "stdafx.h"
#include "ClearObject.h"
#include "WaterPillar.h"
#include "BillBoardGauge.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		weak_ptr<MapManager> m_mapManager;//�}�b�v�}�l�[�W���[
		shared_ptr<MapManager> m_lockMapManager;//�}�b�v�}�l�[�W���[

		shared_ptr<ClearObject> m_clearObject;//�����ȕ�
		shared_ptr<WaterPillar> m_waterPillar;//����
		shared_ptr<BillBoard> m_billBoard;//�r���{�[�h
		shared_ptr<BillBoardGauge> m_billBoardSecond;//2�߂̃r���{�[�h

		shared_ptr<Stage> m_stage;//������X�e�[�W

		vector<weak_ptr<Enemy>> m_upEnemyVec;//�ł��グ��G�|�C���^�̔z��

		int m_charen;//�i�s�x

		float m_coolTime;//���Ԃ𑪂邽�߂ɕK�v
		float m_stanbyTime;//���Ԃ𑪂邽�߂ɕK�v
		float m_blinkingTime;//�_�ł��鎞�Ԃ𑪂�
		float m_billBoardTime;//�r���{�[�h���o�Ă��鎞�Ԃ𑪂�
		float m_playerUpTime;//�}���z�[������o�ăv���C���[�����ނƏオ�鎞�Ԍv��

		bool m_playerStanbyFlag;//�v���C���[�����ނ��܂t���O
		bool m_UpdateFlag;//�A�b�v�f�[�g���邩�̃t���O

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
		void OnCollisionExcute(shared_ptr<GameObject>& other)override;//���葱���Ă���Ƃ��ɏ���
		void OnCollisionExit(shared_ptr<GameObject>& other)override;//���ꂽ�Ƃ��ɏ���

		//�R���W�����ɂ���ēG��v���C���[�������������̏���
		void CollisionUpManhole(shared_ptr<Enemy> enemy,shared_ptr<Player> player);

		int GetState();//�Q�b�^�[
		void SetUpdateSwitch(bool onOff);//�A�b�v�f�[�g���邩�̃Z�b�^�[
	};

}
//end basecross
