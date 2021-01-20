using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.SceneManagement;

//岩を食べる敵の動きを管理するクラス
public class AI_StoneEater : MonoBehaviour
{
	//ナビメッシュエージェントを取得
	private NavMeshAgent agent;

	//目標物が割り当てられているレイヤー
	[SerializeField]
	private LayerMask stoneLayer;

	//目標物の探索半径
	[SerializeField]
	private float searchRadius;

	//取得したものを格納するリスト
	private List<Collider> stoneList = new List<Collider>();

	//目標物の位置を格納
	Vector3 targetPosition;
	float posY;

	//岩を食べた時のエフェクト
	[SerializeField]
	GameObject eatEffect;

	//自身を生成したスポナー
	[SerializeField]
	private EnemySpawner spawner = null;
	public EnemySpawner Spawner
	{
		get { return spawner; }
		set { spawner = value; }
	}

	//個体ごとの速度を格納する変数
	private float moveSpeed;
	public float MoveSpeed
	{
		get { return moveSpeed; }
		set { moveSpeed = value; }
	}

	//個体ごとの経路再設定間隔を格納する変数
	private float searchInterval;
	public float SearchInterval
	{
		get { return searchInterval; }
		set { searchInterval = value; }
	}

	//現在のシーン名を格納する変数
	string currentSceneName;

	void Start()
	{
		//NavMeshAgentを取得
		agent = GetComponent<NavMeshAgent>();

		//自身の高さを格納
		posY = transform.position.y;

		//個体ごとの速度を設定
		agent.speed = moveSpeed;

		//探索コルーチンの開始
		StartCoroutine(OnSearchStone());

		//現在のシーン名を格納
		currentSceneName = SceneManager.GetActiveScene().name;
	}

	//クリスタルを探索する処理を定期的に繰り返す
	IEnumerator OnSearchStone()
	{
		while (true)
		{
			if (!agent.hasPath)
				SetTargetStone();

			//一定時間待機
			yield return new WaitForSeconds(searchInterval);
		}
	}

	//クリスタルを探索する処理
	void SetTargetStone()
	{
		//見つけたクリスタルのリストを空にする
		stoneList.Clear();

		//探索半径内のクリスタルを全取得
		stoneList.AddRange(Physics.OverlapSphere(transform.position, searchRadius, stoneLayer));

		//見つからなかった場合何もしない
		if (stoneList.Count == 0)
		{
			return;
		}
		else
		{
			//取得した岩からランダムに1つを目的地に設定
			targetPosition = stoneList[Random.Range(0, stoneList.Count)].transform.position;

			//高さを自分と同じ位置に補正
			targetPosition.y = posY;

			//決まった岩を目的地に設定
			agent.SetDestination(targetPosition);
		}
	}

	//探索半径を視覚的に表示(シーンビューのみ)
	void OnDrawGizmosSelected()
	{
		Gizmos.color = Color.green;
		Gizmos.DrawWireSphere(transform.position, searchRadius);
	}

	//経路の削除
	void ResetPath()
	{
		agent.ResetPath();
	}

	//特定のオブジェクトに当たった時の処理
	private void OnCollisionEnter(Collision collision)
	{
		//クリスタルに接触時
		if (collision.gameObject.CompareTag("Score"))
		{
			var breakCrystal = collision.gameObject.GetComponent<BreakCrystal>();
			if (breakCrystal != null)
			{
				breakCrystal.GetRootSpawner();
			}

			//ゲーム中の場合のみ、食べたときのSEを再生
			if (currentSceneName == "main")
				MainScene.Instance.PlaySE.PlayEnemyEatSE();

			//クリスタルを削除
			Destroy(collision.gameObject);

			//食べた時のエフェクトを再生
			Instantiate(eatEffect, transform);

			//経路を削除
			ResetPath();
		}
	}
}
