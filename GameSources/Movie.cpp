/*!
@file Movie.cpp
@brief ムービー関係の親クラス
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Movie::Movie(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	Movie::~Movie()
	{

	}

	void Movie::OnCreate()
	{

	}

	void Movie::OnUpdate()
	{

	}

	//ムービー用のカメラに変更させる
	void Movie::CameraChange()
	{
		
	}


}
//end basecross
