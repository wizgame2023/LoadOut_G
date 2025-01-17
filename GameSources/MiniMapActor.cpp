/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapActor::MiniMapActor(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> parentObj, wstring textureName, Vec2 size,
									Vec3 miniMapStartPos, float mapSize, float miniMapSize,
									Vec3 pos, Vec3 rot, Col4 color) :
		Sprite(stagePtr, textureName, size, pos, rot, color),
		m_parentObj(parentObj),
		m_miniMapStartPos(miniMapStartPos),
		m_mapSize(mapSize),
		m_miniMapSize(miniMapSize),
		m_mapMagnification(m_miniMapSize / m_mapSize)
	{

	}

	MiniMapActor::~MiniMapActor()
	{

	}

	void MiniMapActor::OnUpdate()
	{
		//���ƂȂ�I�u�W�F�N�g���������ꍇ�A������������
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<MiniMapActor>(GetThis<MiniMapActor>());
			return;
		}


		//auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		//auto playerPos = player->GetComponent<Transform>()->GetPosition();
		auto actorPos = m_parentObj.lock()->GetComponent<Transform>()->GetPosition();
		
		//Player�̃|�W�V�������~�j�}�b�v�̍��W�ɕϊ�����
		auto trans = GetComponent<Transform>();

		actorPos.y = actorPos.z;
		actorPos.z = 5.0f;


		m_pos = Vec3((actorPos.x*m_mapMagnification)+m_miniMapStartPos.x,(actorPos.y*m_mapMagnification)+m_miniMapStartPos.y,0.0f);

		trans->SetPosition(m_pos);

		SetDrawLayer(11);

	}




}
//end basecross
