/*!
@file SpriteNum.cpp
@brief �������o���X�v���C�g �쐬�r��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	SpriteNum::SpriteNum(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,int num,Vec3 pos, Vec3 rot):
		GameObject(stagePtr),
		m_textureName(textureName),
		m_size(size),
		m_pos(pos),
		m_rot(rot),
		m_num(num)
	{

	}

	SpriteNum::~SpriteNum()
	{

	}

	void SpriteNum::OnCreate()
	{
		// �|���S���̎���
		Col4 color(1, 1, 1, 1); // �|���S���̐F
		const float w = 200.0f; // �|���S���̕�
		const float h = 100.0f; // �|���S���̍���
		m_vertices = { // ���_�f�[�^

			//             ���W                          ,���_�F,     UV���W
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f*(m_num-1), 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f*m_num, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f*(m_num-1), 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f*m_num, 1.0f)}, // 3
		};

		m_indices = { // ���_�C���f�b�N�X�i���_�̂Ȃ����j
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

		//m_vertices[0].textureCoordinate = Vec2(0.0f, 0.0f);

		////���Ԍo�߂Ő��l���ς��悤�ɂ���
		//for (auto num : m_vertices)
		//{

		//}

	}

	void SpriteNum::OnUpdate()
	{
		Col4 color(1, 1, 1, 1); // �|���S���̐F

		m_vertices = { // ���_�f�[�^

			//             ���W                          ,���_�F,     UV���W
			{Vec3(-m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f * (m_num - 1), 0.0f)}, // 0
			{Vec3(+m_size.x * 0.5f, +m_size.y * 0.5f, 0), color, Vec2(0.1f * m_num, 0.0f)}, // 1
			{Vec3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f * (m_num - 1), 1.0f)}, // 2
			{Vec3(+m_size.x * 0.5f, -m_size.y * 0.5f, 0), color, Vec2(0.1f * m_num, 1.0f)}, // 3
		};

		//for (int i = 0; i < m_vertices.size(); i++)
		//{

		//}
		GetComponent<PCTSpriteDraw>()->UpdateVertices(m_vertices);
		//Vec2 uv = m_vertices[0].textureCoordinate;
		//auto test = uv;

		auto a = 0;//�f�o�b�N�p

		//m_drawComp->

		//AddComponent<PCTSpriteDraw>(m_vertices, m_indices); // �X�v���C�g�p�̃h���[�R���|�[�l���g
		//auto a = GetComponent<PCTSpriteDraw>();

	}

	void SpriteNum::SetNum(int num)
	{
		m_num = num;
	}

}
//end basecross
