using UnityEngine;

//武器が特定のオブジェクトに当たった際の処理
public class HitObjectWeapon : MonoBehaviour
{
	//チェインクラスを格納
	[SerializeField]
	private Chain chain;

	//敵破壊時のエフェクト
	[SerializeField]
	private GameObject destroyEffect;

	private void OnCollisionEnter(Collision collision)
	{
		//敵にヒットした場合
		if (collision.gameObject.CompareTag("Enemy"))
		{
			Transform breakPos = collision.gameObject.transform;

			//敵にヒットしたSE再生
			MainScene.Instance.PlaySE.PlayEnemyHitSE();
			MainScene.Instance.PlaySE.PlayImpactSE();
			MainScene.Instance.PlaySE.PlayWeaponHitSE();

			//エフェクト再生
			Instantiate(destroyEffect, transform);

			//カメラを揺らす処理
			MainScene.Instance.GetMainCamera.GetComponent<CameraShake>().Shake(0.4f, 0.1f);

			//敵を削除
			Destroy(collision.gameObject);

			//スポナーごとに生成済みフラグ変更
			var enemyAI = collision.gameObject.GetComponent<AI_StoneEater>();
			if (enemyAI != null)
			{
				enemyAI.Spawner.ChangeIsSpawn();
			}
		}
		//ボーナス敵にヒットした場合
		if (collision.gameObject.CompareTag("Bonus"))
		{
			//敵にヒットしたSE再生
			MainScene.Instance.PlaySE.PlayEnemyHitSE();
			MainScene.Instance.PlaySE.PlayImpactSE();
			MainScene.Instance.PlaySE.PlayWeaponHitSE();

			//カメラを揺らす処理
			MainScene.Instance.GetMainCamera.GetComponent<CameraShake>().Shake(0.4f, 0.1f);

			//強化クリスタル生成
			var quickAI = collision.gameObject.GetComponent<AI_QuickEnemy>();
			if (quickAI != null)
			{
				quickAI.GeneratePowerStone();
			}

			//敵を削除
			Destroy(collision.gameObject);
		}
		//クリスタルにヒットした場合
		if (collision.gameObject.CompareTag("Score"))
		{
			//SE再生
			MainScene.Instance.PlaySE.PlayImpactSE();
			MainScene.Instance.PlaySE.PlayWeaponHitSE();
			MainScene.Instance.PlaySE.PlayBreakSE();

			//カメラを揺らす処理
			MainScene.Instance.GetMainCamera.GetComponent<CameraShake>().Shake(0.4f, 0.1f);

			//クリスタルの自壊コルーチンを実行
			var breakScript = collision.gameObject.GetComponent<BreakCrystal>();
			if (breakScript != null)
			{
				breakScript.BreakSelf();
			}

			//クリスタルの破壊数を追加
			MainScene.Instance.AddBreakCount();

			//チェイン数加算
			chain.AddChain(collision.gameObject.transform.position);
		}
		//強化クリスタルにヒットした場合
		if (collision.gameObject.CompareTag("PowerUp"))
		{
			//SE再生
			MainScene.Instance.PlaySE.PlayImpactSE();
			MainScene.Instance.PlaySE.PlayWeaponHitSE();
			MainScene.Instance.PlaySE.PlayPowerdBreakSE();

			//カメラを揺らす処理
			MainScene.Instance.GetMainCamera.GetComponent<CameraShake>().Shake(0.4f, 0.1f);

			//プレイヤーの強化メソッドを実行
			MainScene.Instance.GetPlayer.GetComponent<PlayerPowerup>().PowerUp();

			//クリスタルの自壊コルーチンを実行
			var breakScript = collision.gameObject.GetComponent<BreakCrystal>();
			if (breakScript != null)
			{
				breakScript.BreakSelf();
			}

			//チェイン数加算
			chain.AddChain(collision.gameObject.transform.position);
		}
	}
}
