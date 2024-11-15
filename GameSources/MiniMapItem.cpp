/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapItem::MiniMapItem(shared_ptr<Stage>& stagePtr,weak_ptr<Item> parentObj, wstring textureName, Vec2 size,int layer, Vec3 pos,  Vec3 rot) :
		GameObject(stagePtr),
		m_textureName(textureName),
		m_parentObj(parentObj),
		m_size(size),
		m_pos(pos),
		m_layer(layer)
	{

	}

	MiniMapItem::~MiniMapItem()
	{
	}

	void MiniMapItem::OnCreate()
	{
		// �|���S���̎���
		m_color = Col4(1, 1, 1, 1); // �|���S���̐F
		const float w = 200.0f; // �|���S���̕�
		const float h = 100.0f; // �|���S���̍���
		vector<VertexPositionColorTexture> m_vertices = { // ���_�f�[�^
			//             ���W                          ,���_�F,     UV���W
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), m_color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // ���_�C���f�b�N�X�i���_�̂Ȃ����j
			0, 1, 2, // ������ň�̃|���S��(�O�p�`)
			2, 1, 3  // ����������
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // �X�v���C�g�p�̃h���[�R���|�[�l���g
		drawComp->SetTextureResource(m_textureName);//�e�N�X�`���̖��O�w��
		drawComp->SetSamplerState(SamplerState::LinearWrap); // �e�N�X�`�����J��Ԃ��ē\��t����ݒ�
		drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // �|���S����F��ݒ肷��

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);


		// �A���t�@�u�����h(���ߏ���)��L���ɂ���
		SetAlphaActive(true); // true:���߂�L���Afalse:���߂𖳌�

		SetDrawLayer(m_layer);

	}

	void MiniMapItem::OnUpdate()
	{
		//���ƂȂ�I�u�W�F�N�g���������ꍇ�A������������
		if (!m_parentObj.lock())
		{
			GetStage()->RemoveGameObject<MiniMapItem>(GetThis<MiniMapItem>());
		}
	}

}
//end basecross
