using System.Collections;
using UnityEngine;

//各スポナーの親クラス
public class Spawner : MonoBehaviour
{
	//生成するプレハブを指定します
	[SerializeField]
	private GameObject spawnPrefab = null;

	//出現間隔
	[SerializeField]
	private float interval = 0;

	//最初の生成までの待機時間
	[SerializeField]
	private float coolTime;

	//生成したオブジェクト
	protected GameObject spawnObject;

	//生成済みフラグ
	bool isSpawned = false;

	//起伏に対応するためのRay
	Ray ray;
	RaycastHit hit;

	//コルーチンの自動スタートフラグ
	//生成する敵によって継承先で指定
	[SerializeField]
	protected bool isAutoSpawn = true;

	void Start()
	{
		if (isAutoSpawn)
			StartCoroutine(CoolTime());
	}

	//一番最初に出現するまでの待機時間
	IEnumerator CoolTime()
	{
		yield return new WaitForSeconds(coolTime);
		StartCoroutine(SpawnLoop());
		yield break;
	}

	//生成処理をループするコルーチン
	IEnumerator SpawnLoop()
	{
		while (true)
		{
			//生成済みフラグがfalseなら実行
			if (!isSpawned)
			{
				Spawn();
			}
			yield return new WaitForSeconds(interval);
		}
	}

	//生成処理の本体
	//一度だけや特定のタイミングで生成したい場合はこちらを呼ぶ
	virtual protected void Spawn()
	{
		//生成する高さを入れる一時変数
		float posY = 0;

		//地形の起伏に対応した生成ロジック
		//高所からRayを飛ばし、ヒットした位置を生成するY座標とする
		ray = new Ray(new Vector3(transform.position.x, 200, transform.position.z), -transform.up);
		if (Physics.Raycast(ray, out hit, 1000f))
		{
			posY = hit.point.y;
		}
		Debug.DrawRay(transform.position, -transform.up * 1000f, Color.yellow);

		//オブジェクトを生成
		spawnObject = Instantiate(spawnPrefab, new Vector3(transform.position.x, posY, transform.position.z), Quaternion.identity);

		//この地点の存在フラグをtrueに
		isSpawned = true;

		//生成時の処理
		SpawnSomething();
	}

	//スポーン時に何かしたいときの処理
	//オーバーライド先で中に処理を入れて使う
	protected virtual void SpawnSomething()
	{
		return;
	}

	//生成済みフラグの変更
	public void ChangeIsSpawn()
	{
		isSpawned = false;
	}
}
