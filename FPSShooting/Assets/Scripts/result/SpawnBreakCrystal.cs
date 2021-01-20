using System.Collections;
using UnityEngine;

//リザルトのクリスタル生成を管理するクラス
public class SpawnBreakCrystal : MonoBehaviour
{
	//生成するクリスタルのプレハブ
	[SerializeField]
	GameObject crystalPrefab;

	//生成コルーチンを呼び出す関数
	public void startSpawn(int count)
	{
		var crystalNum = count;
		StartCoroutine(SpawnCrystal(crystalNum));
	}

	//クリスタルの生成を行うコルーチン
	IEnumerator SpawnCrystal(int crystalNum)
	{
		//引数で受けとった数だけ、一定範囲内にクリスタルを生成
		for (int i = 0; i < crystalNum; i++)
		{
			float offsetX = transform.position.x + Random.Range(-5, 5);
			float offsetZ = transform.position.z + Random.Range(-5, 5);

			Instantiate(crystalPrefab, new Vector3(offsetX, transform.position.y, offsetZ), Quaternion.identity);

			yield return new WaitForSeconds(.1f);
		}

		yield break;
	}
}
