/*!
@file MovieGameClear.h
@brief �Q�[���N���A�̃��[�r�[
*/

#pragma once
#include "stdafx.h"
#include "Movie.h"

namespace basecross {
	class MovieGameClear :public Movie
	{
	private:
		Vec3 m_tagetPos;//�ړI�n
	public:
		MovieGameClear(shared_ptr<Stage>& stagePtr);
		~MovieGameClear();

		void OnCreate()override;
		void OnUpdate()override;

	};


}
//end basecross
