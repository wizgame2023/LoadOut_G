/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Sprite::Sprite(shared_ptr<Stage>& stagePtr,wstring textureName,Vec2 size,Vec3 pos,Vec3 rot, Col4 color,int layer) :
		GameObject(stagePtr),
		m_textureName(textureName),
		m_size(size),
		m_pos(pos),
		m_color(color),
		m_layer(layer)
	{

	}

	Sprite::~Sprite()
	{
	}

	void Sprite::OnCreate()
	{
		// �|���S���̎���
		Col4 color(1, 1, 1, 1); // �|���S���̐F
		const float w = 200.0f; // �|���S���̕�
		const float h = 100.0f; // �|���S���̍���
		vector<VertexPositionColorTexture> m_vertices = { // ���_�f�[�^
			//             ���W                          ,���_�F,     UV���W
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.0f, 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(1.0f, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.0f, 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(1.0f, 1.0f)}, // 3
		};

		vector<uint16_t> m_indices = { // ���_�C���f�b�N�X�i���_�̂Ȃ����j
			0, 1, 2, // ������ň�̃|���S��(�O�p�`)
			2, 1, 3  // ����������
		};

		m_drawComp = AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // �X�v���C�g�p�̃h���[�R���|�[�l���g
		m_drawComp->SetTextureResource(m_textureName);//�e�N�X�`���̖��O�w��
		m_drawComp->SetSamplerState(SamplerState::LinearWrap); // �e�N�X�`�����J��Ԃ��ē\��t����ݒ�
		m_drawComp->SetDiffuse(Col4(1, 1, 1, 1.0f)); // �|���S����F��ݒ肷��

		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);


		// �A���t�@�u�����h(���ߏ���)��L���ɂ���
		SetAlphaActive(true); // true:���߂�L���Afalse:���߂𖳌�

		SetDrawLayer(m_layer);

	}

	void Sprite::OnUpdate()
	{
		
	}

	//�J���[�̐��l��ύX����
	void Sprite::SetColor(Col4 color)
	{
		m_color = color;
		m_drawComp->SetDiffuse(m_color);
	}
	//�J���[�̐��l���擾������
	Col4 Sprite::GetColor()
	{
		return m_color;
	}

	//�������g����������
	void Sprite::MyDestroy()
	{
		GetStage()->RemoveGameObject<Sprite>(GetThis<Sprite>());
	}

}
//end basecross
