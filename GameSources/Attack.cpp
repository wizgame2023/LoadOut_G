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
		if (m_count == 0)
		{
			m_Owner->GetGameOverScene();
			m_count++;
		}		
		//m_Owner->ChangeState<Patrol>();
	}

	void Attack::OnExit()
	{

	}
}
//end basecross
