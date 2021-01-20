using UnityEngine;

//スポナークラスを継承した、岩を食べる敵の生成スクリプト
public class EnemySpawner : Spawner
{
	//パラメーター決定時の最小移動速度
	[SerializeField]
	float minSpeed;

	//パラメーター決定時の最大移動速度
	[SerializeField]
	float maxSpeed;

	//パラメーター決定時の最短探索間隔
	[SerializeField]
	float minSearchInterval;

	//パラメーター決定時の最長探索間隔
	[SerializeField]
	float maxSearchInterval;

	protected override void SpawnSomething()
	{
		MainScene.Instance.PlaySE.PlayEnemySpawnSE();
		SetEnemyParam();
	}

	//生成した敵のパラメーターを設定
	void SetEnemyParam()
	{
		//移動速度の設定
		float moveSpeed = Random.Range(minSpeed, maxSpeed);
		moveSpeed = Mathf.Floor(moveSpeed * 10) / 10;

		//探索間隔の設定
		float searchInterval = Random.Range(minSearchInterval, maxSearchInterval);
		searchInterval = Mathf.Floor(searchInterval * 10) / 10;

		var enemyAI = spawnObject.GetComponent<AI_StoneEater>();
		if (enemyAI != null)
		{
			//移動速度
			enemyAI.MoveSpeed = moveSpeed;
			//クリスタルの探索間隔
			enemyAI.SearchInterval = searchInterval;
			//自身を生成したスポナー
			enemyAI.Spawner = this;

			Debug.Log("移動速度" + moveSpeed + "、探索間隔" + searchInterval + "の敵を生成");
		}
	}
}
