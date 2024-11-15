/*!
@file Sprite.h
@brief �����I�u�W�F�N�g���~�j�}�b�v�ɕ\��
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class MiniMapActor :public Sprite
	{
	private:
		Vec3 m_miniMapStartPos;//�~�j�}�b�v�̏����ʒu
		float m_mapSize;//�}�b�v�̑傫��(���a)
		float m_miniMapSize;//�~�j�}�b�v�̑傫��(���a)
		float m_mapMagnification;//�~�j�}�b�v�p�̔{��

		weak_ptr<Actor> m_parentObj;//�e�I�u�W�F�N�g
		//Vec3 m_miniMapPos;
	public:
		MiniMapActor(shared_ptr<Stage>& stagePtr,weak_ptr<Actor> parentObj, wstring textureName, Vec2 size,
			Vec3 miniMapStartPos,float mapSize,float miniMapSize,
			Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f));//�R���X�g���N�^
		~MiniMapActor();//�f�X�g���N�^

		//void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V
	};


}
//end basecross
