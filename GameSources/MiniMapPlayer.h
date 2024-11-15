/*!
@file Sprite.h
@brief �X�v���C�g�p�̃N���X
*/

#pragma once
#include "stdafx.h"
#include "Sprite.h"

namespace basecross {
	class MiniMapPlayer :public Sprite
	{
	private:
		Vec3 m_miniMapStartPos;//�~�j�}�b�v�̏����ʒu
		float m_mapSize;//�}�b�v�̑傫��(���a)
		float m_miniMapSize;//�~�j�}�b�v�̑傫��(���a)
		float m_mapMagnification;//�~�j�}�b�v�p�̔{��
		//Vec3 m_miniMapPos;
	public:
		MiniMapPlayer(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,
			Vec3 miniMapStartPos,float mapSize,float miniMapSize,
			Vec3 pos = Vec3(0.0f, 0.0f, 0.0f), Vec3 rot = Vec3(0.0f, 0.0f, 0.0f), Col4 color = Col4(1.0f, 1.0f, 1.0f, 1.0f));//�R���X�g���N�^
		~MiniMapPlayer();//�f�X�g���N�^

		//void OnCreate()override;//�쐬
		void OnUpdate()override;//�X�V
	};


}
//end basecross
