/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	TrackingPillarEfect::TrackingPillarEfect(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> actor, Vec3 pos, wstring textureName, Vec2 velocity, int square) :
		PillarEffect(stagePtr,pos,textureName,velocity,square),
		m_actor(actor)
	{

	}
	//�f�X�g���N�^
	TrackingPillarEfect::~TrackingPillarEfect()
	{

	}

	//�X�V
	void TrackingPillarEfect::OnUpdate()
	{
		//�t���O���I���ɂȂ�����A�b�v�f�[�g����
		if (!m_move) return;

		auto actor = m_actor.lock();
		//�ǔ����錳�����Ȃ��Ȃ�Ύ��������Ȃ��Ȃ�
		if (!actor)
		{
			GetStage()->RemoveGameObject<TrackingPillarEfect>(GetThis<TrackingPillarEfect>());
			return;
		}

		auto actorPos = actor->GetComponent<Transform>()->GetPosition();
		float delta = App::GetApp()->GetElapsedTime();

		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv���W�����炵�Ă���
			auto test = 0;
		}

		auto Trans = GetComponent<Transform>();
		auto pos = GetComponent<Transform>()->GetPosition();
		pos = actorPos;
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
