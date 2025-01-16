/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{

	BillBoard::BillBoard(const shared_ptr<Stage>& StagePtr,
		shared_ptr<GameObject>& actorPtr, size_t Number,float pushY,Vec3 scale) :
		GameObject(StagePtr),
		m_actor(actorPtr),
		m_Number(Number),
		m_textureName(L"Clear"),
		m_pushY(pushY),
		m_scale(scale),
		m_color(Col4(1.0f,1.0f,1.0f,1.0f))
	{}
	BillBoard::BillBoard(const shared_ptr<Stage>& StagePtr,
		shared_ptr<GameObject>& actorPtr, wstring spriteName,float pushY,Vec3 scale,Col4 color) :
		GameObject(StagePtr),
		m_actor(actorPtr),
		m_Number(0),
		m_textureName(spriteName),
		m_pushY(pushY),
		m_scale(scale),
		m_color(color)
	{}
	BillBoard::~BillBoard() {}

	//������
	void BillBoard::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_actor.expired()) {
			auto SeekPtr = m_actor.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += m_pushY;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(m_scale);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//�ύX�ł���X�N�G�A���\�[�X���쐬

			//���_�z��
			//vector<VertexPositionNormalTexture> vertices;
			//�C���f�b�N�X���쐬���邽�߂̔z��
			vector<uint16_t> indices;
			//Square�̍쐬(�w���p�[�֐��𗘗p)
			MeshUtill::CreateSquare(1.0f, m_vertices, indices);
			//UV�l�̕ύX
			//���㒸�_
			m_vertices[0].textureCoordinate = Vec2(0, 0);
			//�E�㒸�_
			m_vertices[1].textureCoordinate = Vec2(1, 0);
			//�������_
			m_vertices[2].textureCoordinate = Vec2(0, 1.0f);
			//�E�����_
			m_vertices[3].textureCoordinate = Vec2(1, 1.0f);

			//���_�̌^��ς����V�������_���쐬
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : m_vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//�V�������_���g���ă��b�V�����\�[�X�̍쐬
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_textureName);
			SetAlphaActive(true);
			SetDrawLayer(2);
		}

	}
	void BillBoard::OnUpdate() {
		if (m_actor.expired())
		{
			GetStage()->RemoveGameObject<BillBoard>(GetThis<BillBoard>());
		}
		if (!m_actor.expired()) {
			auto SeekPtr = m_actor.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += m_pushY;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(m_scale);

			auto DrawComp = GetComponent<PCTStaticDraw>();
			DrawComp->SetTextureResource(m_textureName);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//�������J�����ڐ��ɂ���
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

	}

	//�r���{�[�h�̃e�N�X�`���ύX
	void BillBoard::ChangeTexture(wstring textureName)
	{
		m_textureName = textureName;
	}

	//�T�C�Y�̃Z�b�^�[
	void BillBoard::SetScale(Vec3 scale)
	{
		m_scale = scale;
	}

	//�o�����鍂���̃Z�b�^�[
	void BillBoard::SetPushY(float pushY)
	{
		m_pushY = pushY;
	}
	

}
//end basecross
