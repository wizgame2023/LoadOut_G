/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"

namespace basecross{
	class Player :public GameObject
	{
	private:
		Vec3 m_Pos;//ポジション
		Vec3 m_Rot;//回転度

		int m_count;//アイテムの所持数、この数の分だけマンホールを上げれる
		int m_hp = 3;//Playerの体力

		float m_deg;//角度

		shared_ptr<Transform> m_Trans;//トランスフォーム

		shared_ptr<InputDevice> m_Device;//コントローラー
		CONTROLER_STATE m_controler;//コントローラー

		//float m_time;//テスト用使わなくなったら消してください

	public:
		Player(const shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot);//コンストラクタ
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//マンホールの上に罠を設置する
		void SetUp();

		void AddCount(int add);
		void PlayerMove();
		void ManholeSet(Vec3 pos);//マンホールの上にわなを仕掛ける

		void OnCollisionEnter(shared_ptr<GameObject>& other);//当たり判定
	};

}
//end basecross

