using UnityEngine;

//スポナークラスを継承した岩生成スクリプト
public class StoneSpawner : Spawner
{
	//スポーン時処理メソッドのオーバーライド
	protected override void SpawnSomething()
	{
		PlaySpawnAnimation();
		SetSpawner();
	}

	//クリスタルの出現時アニメーション再生
	void PlaySpawnAnimation()
	{
		if (spawnObject.GetComponent<Animator>())
		{
			Debug.Log("Animator取得");
			spawnObject.GetComponent<Animator>().SetTrigger("spawn");
		}
	}

	//生成したクリスタルのスポナーとして自身を登録
	void SetSpawner()
	{
		var breakCrystal = spawnObject.GetComponent<BreakCrystal>();
		if (breakCrystal != null)
		{
			breakCrystal.SetSpawner = gameObject;
		}
	}
}
