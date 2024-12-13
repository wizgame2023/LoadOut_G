/*!
@file PillarEffect.cpp
@brief ����̃G�t�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�R���X�g���N�^
	PillarEffect::PillarEffect(const shared_ptr<Stage>& stagePtr,Vec3 pos, wstring textureName,Vec2 velocity, int square):
		GameObject(stagePtr),
		m_height(10.0f),
		m_topRadius(4.5f),
		m_bottomRadius(4.5f),
		m_square(square),
		m_loops(1.0f, 1.0f),
		m_topColor(1.0f, 1.0f, 1.0f, 1.0f),
		m_bottomColor(1.0f, 1.0f, 1.0f, 1.0f),
		m_textureName(textureName),
		m_scrollVelocity(velocity),
		m_pos(pos)
	{

	}
	//�f�X�g���N�^
	PillarEffect::~PillarEffect()
	{
	}

	void PillarEffect::InitializeVertices()
	{
		////�|���S���̒��_�f�[�^
		m_vertices.clear();
		m_vertices.reserve((m_square+1)*2);
		for (int i = 0; i <= m_square; i++)
		{
			Vec3 pos;//���_���W
			VertexPositionColorTexture vPCT; // 1���_�̃f�[�^

			// �㉺�̒��_�̋��ʃf�[�^
			float rad = XMConvertToRadians(360.0f * i / m_square);
			//uv���W
			float u = (m_loops.x * static_cast<float>(i) / static_cast<float>(m_square))+m_test.x;
			float v = m_loops.y+m_test.y;

			// ��̉~�̒��_
			pos = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_topRadius + Vec3(0.0f, m_height, 0.0f)+m_pos; // Y���W��m_height�����炷
			vPCT = VertexPositionColorTexture(pos, m_topColor, Vec2(u, 0)); // V���W���ŏ��l�ɂ���
			m_vertices.push_back(vPCT);

			// ���̉~�̒��_
			pos = Vec3(cosf(rad), 0.0f, sinf(rad)) * m_bottomRadius+m_pos;
			vPCT = VertexPositionColorTexture(pos, m_bottomColor, Vec2(u, v)); // V���W���ő�l�ɂ���
			m_vertices.push_back(vPCT);

		}

		// ���_�C���f�b�N�X(���_���Ȃ��鏇��)
		const vector<uint16_t> baseIndices = {
			 2, 1, 0,
			 3, 1, 2,
		};

		m_indices.clear();
		m_indices.reserve(m_square * baseIndices.size());//�x���~���_�C���f�b�N�X
		for (int i = 0; i < m_square; i++)
		{
			// baseIndices�̐��������[�v
			for (auto baseIndex : baseIndices)
			{
				//���_�C���f�b�N�X���P�̎l�p���ƂɂQ����邽�߂������Ă���
				m_indices.push_back(baseIndex + (2 * i));
			}
		}

	}

	void PillarEffect::OnCreate()
	{
		m_pos.y = 0;
		InitializeVertices();

		m_drawComp = AddComponent<BcPCTStaticDraw>();//Bc�t���łȂ��Ƃ����Ȃ�
		m_drawComp->SetOriginalMeshUse(true);
		m_drawComp->CreateOriginalMesh(m_vertices, m_indices);
		m_drawComp->SetSamplerState(SamplerState::LinearWrap);//�e�N�X�`�������[�v������
		m_drawComp->SetDepthStencilState(DepthStencilState::Read);//�����̃I�u�W�F�N�g����Z�o�b�t�@�𖳎�
		m_drawComp->SetBlendState(BlendState::Additive);
		m_drawComp->SetTextureResource(m_textureName);

		SetAlphaActive(true);
		m_isUpdate = false;

	}

	void PillarEffect::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		for (auto& vertex : m_vertices)
		{
			vertex.textureCoordinate += m_scrollVelocity * delta;//uv���W�����炵�Ă���
			auto test = 0;
		}
		//m_test += m_scrollVelocity * delta;//uv���W�����炵�Ă���


		if (m_isUpdate)
		{
			m_isUpdate = false;	
			InitializeVertices();
		}

		m_drawComp->UpdateVertices(m_vertices);

	}

	void PillarEffect::UpdateTest(bool OnOff)
	{
		m_isUpdate = OnOff;
	}

	//void PillarEffect::SetScrollPerSecond()

}
//end basecross
