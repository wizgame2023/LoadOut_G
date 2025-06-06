/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once

#include"Actor.h"//動くオブジェクトの親クラス

//ツール用
#include"RaySphere.h";//レイの当たり判定
#include"Ray.h";//レイ
#include"MathTools.h";//数学計算用ツール
#include"AStar.h";//経路探査処理

//ステート用
#include"State.h"//ステートの親クラス
#include"Tracking.h"
#include"State.h"
#include"Patrol.h"
#include"Attack.h"
#include"RepopEnemy.h"

//親クラス用
#include"Actor.h"

#include"ProjectShader.h"
#include"ProjectBehavior.h"
#include"Scene.h"
#include"GameStage.h"
#include"Character.h"
#include"Player.h"
#include"Block.h"
#include"TubakiStage.h"
#include"YuusinStage.h"
#include"YuutaStage.h"
#include"Ground.h"
#include"MapManager.h"
#include"Battery.h"//電池
#include"Enemy.h"
#include"Manhole.h"
#include"Wall.h"
#include"Sprite.h"//スプライト用
#include"TilteStage.h"//タイトルステージ
#include"GameOverStage.h"//ゲームオーバーステージ
#include"GameClearStage.h"//ゲームクリアステージ
#include"SelectStage.h"
#include"Sky_base.h"
#include"happysky.h"
#include"ClearObject.h"//透明な物理オブジェクト
#include"SpriteNum.h"//数字のスプライト
#include"WaterPillar.h"//水柱
#include"MiniMapActor.h"//ミニマップのPlayerやEnemy　オブジェクトで動くもの
#include"MiniMapItem.h"//ミニマップのItem
#include"BillBoard.h"
#include"Hatch.h"//脱出用のハッチ
#include"Movie.h"//ムービー用の親クラス
#include"MovieGameStart.h"//ゲーム開始時のムービ
#include"MovieUpPlayer.h"//Playerが打ちあがる時のムービー
#include"MovieGameClear.h"
#include"MovieGameOver.h"//ゲームオーバー遷移時ののムービ
#include"MovieUpEnemy.h"//Enemyが打ちあがる時のムービー
#include"MovieUpEandP.h"//EnemyとPlayerが同時に打ちあがる時のムービー
#include"PillarEfect.h"//柱上のエフェクト
#include"ManholeSprite.h"//ミニマップ用のマンホールスプライト
#include"RandomItem.h"//ランダムにイベントが発生するアイテム
#include"GameStage02.h"
#include"GameStage03.h"
#include"GameStage04.h"
#include"GameStage05.h"
#include"GameStage06.h"
#include"GameStage07.h"
#include"GameStage08.h"
#include"GameStage09.h"
#include"GameStage10.h"
#include"GameStage11.h"
#include"GameStage12.h"
#include"GameStage13.h"
#include"GameStage14.h"
#include"GameStage15.h"
#include"GameStage16.h"
#include"GameStage17.h"
#include"GameStage18.h"
#include"GameStage19.h"
#include"GameStage20.h"
#include"BlackOut.h"
#include"TrackingPillarEfect.h"
#include"SpriteMove.h"

//マネージャー用
#include"MiniMapManager.h"//ミニマップ生成
#include"UIManager.h";//UIマネージャー
#include"StageManager.h"
#include"StageCollisionManager.h"//コリジョン管理
#include"NumberManager.h";

//カメラ用
#include"MyCamera.h"//追尾カメラ用




