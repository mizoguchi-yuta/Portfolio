using System.Collections;
using UnityEngine;

//クリスタルの自壊を管理するクラス
public class BreakCrystal : MonoBehaviour
{
	//破壊時に生成されるパーティクル
	[SerializeField]
	GameObject breakEffect;

	//自身が生成されるスポナー
	private GameObject spawner;
	public GameObject SetSpawner
	{
		set { spawner = value; }
	}

	//自壊を実行するメソッド
	public void BreakSelf()
	{
		Instantiate(breakEffect, transform);
		StartCoroutine(OnBreak());
	}

	//破壊から消えるまでの処理を行うコルーチン
	IEnumerator OnBreak()
	{
		//すでに破壊した岩を敵が検知しないようにレイヤーを変更
		gameObject.layer = 14;

		Rigidbody[] shards;

		//ヒットしたオブジェクトの子要素のRigidbodyをすべて取得
		shards = GetComponentsInChildren<Rigidbody>();

		//取得できなかった場合はリターン
		if (shards.Length == 0)
		{
			yield break;
		}

		//isKinematicを無効化
		for (int i = 0; i < shards.Length; i++)
		{
			shards[i].isKinematic = false;
		}

		//2秒後に破片を消滅
		yield return new WaitForSeconds(2);
		Destroy(gameObject);

		//スポナーの生成済みフラグを変更
		GetRootSpawner();
	}

	//親スポナーの生成済みフラグ変更メソッドを実行
	//敵が食べたときも呼び出せるようpublicアクセスとする
	public void GetRootSpawner()
	{
		//通常クリスタルのスポナーかどうか判定
		var normalCrystal = spawner.GetComponent<StoneSpawner>();

		if (normalCrystal != null)
		{
			normalCrystal.ChangeIsSpawn();
		}
		else
		{
			var powerdCrystal = spawner.GetComponent<PowerdStoneSpawner>();
			if (powerdCrystal != null)
			{
				powerdCrystal.ChangeIsSpawn();
			}
		}
	}
}
