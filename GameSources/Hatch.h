/*!
@file Hatch.h
@brief �n�b�`
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Hatch :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		//weak_ptr<MapManager> m_mapManager;//�}�b�v�}�l�[�W���[

		//shared_ptr<ClearObject> m_clearObject;//�����ȕ�
		//shared_ptr<WaterPillar> m_waterPillar;//����

		int m_charen;//�e�N�X�`����ς���t���O

		float m_time;//���Ԃ𑪂邽�߂ɕK�v

	public:
		Hatch(shared_ptr<Stage>& stagePtr);
		~Hatch();

		void OnCreate()override;
		void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;//�����������ɏ���
	};


}
//end basecross
