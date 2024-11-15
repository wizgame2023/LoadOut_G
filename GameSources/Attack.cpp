/*!
@file Attack.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {


	void Attack::OnStart()
	{
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		App::GetApp()->GetScene<Scene>()->GetActiveStage()->RemoveGameObject<Player>(player);
	}

	void Attack::OnUpdate()
	{
		m_Owner->ChangeState<Patrol>();
	}

	void Attack::OnExit()
	{

	}
}
//end basecross
