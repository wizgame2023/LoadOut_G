/*!
@file Attack.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void Attack::OnStart()
	{
	}

	void Attack::OnUpdate()
	{
		m_Owner->GetGameOverScene();
		//m_Owner->ChangeState<Patrol>();
	}

	void Attack::OnExit()
	{

	}
}
//end basecross
