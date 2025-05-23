/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include "SpriteNum.h"
#include "BillBoard.h"
#include "NumberManager.h"
#include "TrackingPillarEfect.h"

namespace basecross{
	class Player :public Actor
	{
	private:
		Vec3 m_Pos;//ポジション
		Vec3 m_Rot;//回転度

		int m_itemCount;//アイテムの所持数、この数の分だけマンホールを上げれる
		int m_hp = 3;//Playerの体力

		float m_deg;//角度
		float m_speed;//スピード
		float m_pushSpeed;//追加スピード
		float m_pushSpeedCountTime;//追加スピードの経過時間

		bool m_key;//鍵を持っているかどうか
		bool m_addBoardFlag;//ビルボードを出すフラグ
		bool m_gameStageFlag;//ゲームステージかどうか確認するフラグ

		shared_ptr<Transform> m_Trans;//トランスフォーム

		shared_ptr<InputDevice> m_Device;//コントローラー
		CONTROLER_STATE m_controler;//コントローラー
		shared_ptr<NuberManager> m_spriteNum;//数字のスプライト
		shared_ptr<BillBoard> m_billBoard;//ビルボード
		shared_ptr<TrackingPillarEfect> m_pillar;//柱上のエフェクト
	public:
		Player(shared_ptr<Stage>& StagePtr, Vec3 pos,Vec3 rot,bool GameFlag = true);//コンストラクタ
		~Player();

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		//マンホールの上に罠を設置する
		void SetUp();

		void AddCount(int add);
		void PlayerMove();
		void ManholeSet(Vec3 pos);//マンホールの上にわなを仕掛ける

		void OnCollisionEnter(shared_ptr<GameObject>& other);//当たり判定
		void KeyBoardMove();

		float GetAngle()override;//角度を渡す
		int GetBatteryCount();//どれくらいバッテリーを持っているか
		void AddBatteryUI();//電池をどれくらい取得しているかのUI

		void SetKey(bool key);//鍵を持っているかどうか渡す
		bool GetKey();//鍵を持っているかどうか渡す
		void SetPushSpeed(float pushSpeed);//追加するスピードを渡す

		//bool m_move;//動くか動かないかのフラグ

	};

}
//end basecross

