/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	TrackingPillarEfect::TrackingPillarEfect(const shared_ptr<Stage>& stagePtr, Vec3 pos, wstring textureName, Vec2 velocity, int square) :
		PillarEffect(stagePtr,pos,textureName,velocity,square)
	{

	}
	//�f�X�g���N�^
	TrackingPillarEfect::~TrackingPillarEfect()
	{

	}

	//�X�V
	void TrackingPillarEfect::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();
		float delta = App::GetApp()->GetElapsedTime();

		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv���W�����炵�Ă���
			auto test = 0;
		}
		//m_test += m_scrollVelocity * delta;//uv���W�����炵�Ă���
		auto Trans = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();
		playerPos.y = pos.y;
		pos = playerPos;
		Trans->SetPosition(pos);

		if (m_isUpdate)
		{
			m_isUpdate = false;
			InitializeVertices();
		}

		m_drawComp->UpdateVertices(m_vertices);
	}


}
//end basecross
