/*!
@file Actor.cpp
@brief Player��Enemy�ȂǓ����I�u�W�F�N�g�̐e�N���X
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Actor::Actor(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::OnUpdate()
	{
		auto pos = GetComponent<Transform>()->GetPosition();//�|�W�V�����擾
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//�}�b�v�}�l�[�W���[�擾
		Vec2 selPos = mapManager->ConvertSelMap(pos);//������Z�����W���擾
		int selNow = mapManager->SelMapNow(pos);//���݂���Z�����W�ɉ������邩���擾

		//�m�F�����Z�����W���O������Ă�����
		if (selPos != m_selPosNow)
		{
			//������Z�����W��ύX���đO����Z�����W��ۑ�����
			m_selPosBefor = m_selPosNow;
			m_selPosNow = selPos;
		}
	}

	float Actor::GetAngle()
	{
		return m_angle;
	}

	//���݂̃Z�����W�̃Q�b�^�[
	Vec2 Actor::GetSelPosNow()
	{
		return m_selPosNow;
	}

	//�O�����Z�����W�̃Q�b�^�[
	Vec2 Actor::GetSelPosBefor()
	{
		return m_selPosBefor;
	}


	void Actor::SetAngle(float angle)
	{
		m_angle = angle;
	}

	void Actor::MoveSwitch(bool onoff)
	{
		m_move = onoff;
	}


}
//end basecross
