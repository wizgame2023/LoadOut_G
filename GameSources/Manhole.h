/*!
@file Manhole.h
@brief �}���z�[��
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//�|�W�V����
		weak_ptr<MapManager> m_mapManager;//�}�b�v�}�l�[�W���[

	public:
		Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos);
		~Manhole();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
