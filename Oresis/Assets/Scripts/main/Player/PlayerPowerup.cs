using System.Collections;
using UnityEngine;

//プレイヤーの強化を管理するクラス
public class PlayerPowerup : MonoBehaviour
{
	//強化時間
	[SerializeField]
	float powerupTime;

	//プレイヤーの移動を管理するクラス
	[SerializeField]
	PlayerMove playerMove;

	//クラス格納用変数
	[SerializeField]
	HitObjectPlayer hitObjectPlayer;

	//生成するパーティクル
	[SerializeField]
	ParticleSystem speedEffect;

	//強化時の速さ倍率
	[SerializeField]
	float speed;

	//強化時に有効化する全身判定
	[SerializeField]
	GameObject powerupCollider;

	//強化終了時にボーナスエネミーを再度湧かせるためのスポナー
	[SerializeField]
	BonusEnemySpawner bonusSpawner;

	public void PowerUp()
	{
		StartCoroutine(OnPowerUp());
	}

	//強化の開始から終了までを行うコルーチン
	IEnumerator OnPowerUp()
	{
		//SE再生
		MainScene.Instance.PlaySE.PlayPowerUpSE();

		//移動速度倍率を付与
		playerMove.SetSpeedUp = speed;

		//全身判定を有効化
		powerupCollider.SetActive(true);

		//無敵を有効化
		hitObjectPlayer.SetIsInvincible = true;

		//パーティクル生成
		var particle = Instantiate(speedEffect, transform);

		//強化終了まで待つ
		yield return new WaitForSeconds(powerupTime);

		//移動速度倍率を等倍に
		playerMove.SetSpeedUp = 1;

		//全身判定を無効化
		powerupCollider.SetActive(false);

		//無敵を無効化
		hitObjectPlayer.SetIsInvincible = false;

		//パーティクルを破棄
		Destroy(particle.gameObject);

		//ボーナスエネミーを再スポーン
		bonusSpawner.SpawnBonusEnemy();

		yield break;
	}
}
