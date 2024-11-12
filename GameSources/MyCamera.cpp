/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MyCamera::MyCamera(Vec3 pos):
		m_Pos(pos)
	{

	}

	MyCamera::~MyCamera()
	{

	}

	void MyCamera::OnCreate()
	{
	}

	void MyCamera::OnUpdate()
	{
		auto stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();//����ŃQ�b�g�X�e�[�W
		weak_ptr<Player> player = stage->GetSharedGameObject<Player>(L"Player");//�v���C���[�擾

		auto posPlayer = player.lock()->GetComponent<Transform>()->GetPosition();//�|�W�V�����擾
		SetAt(posPlayer);//�����_������

		//�J�����̍��W�����߂�	
		SetEye(m_Pos+posPlayer);

	}

}
//end basecross
