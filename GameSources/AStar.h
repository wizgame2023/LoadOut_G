/*!
@file AStar.h
@brief �o�H�T������
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class AStar :GameObject
	{
	private:

	public:
		AStar(shared_ptr<Stage>& stagePtr);//�R���X�g���N�^
		~AStar();//�f�X�g���N�^

		void OnCreate() override;//�쐬
		void OnUpdate() override;//�X�V
	};

}
//end basecross
