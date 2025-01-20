/*!
@file BillBoardGauge.h
@brief �r���{�[�h�̃Q�[�W����
*/

#pragma once
#include "stdafx.h"
#include "BillBoard.h"

namespace basecross {
	class BillBoardGauge :public BillBoard
	{
	private:
		float m_parsecond;//�S�̂̉��p�[�Z���g�o�������߂�
	public:
		BillBoardGauge(const shared_ptr<Stage>& StagePtr, 
			shared_ptr<GameObject>& actorPtr, wstring spriteName,int layer = 2, float pushY = 18.0f, Vec3 scale = Vec3(3.0f, 3.0f, 3.0f));
		~BillBoardGauge();

		void OnCreate()override;
		void OnUpdate()override;

		void SetPercent(float parcent);//���_�̍X�V
	};

}
//end basecross
