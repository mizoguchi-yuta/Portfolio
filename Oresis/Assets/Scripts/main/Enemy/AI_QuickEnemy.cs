using System.Collections;
using UnityEngine;
using UnityEngine.AI;

//ボーナス敵の動きを管理するクラス
public class AI_QuickEnemy : MonoBehaviour
{
	//ナビメッシュエージェントを取得
	private NavMeshAgent agent;

	//目的地のリスト
	[SerializeField]
	private Transform[] wayPoints;

	//目的地
	Vector3 targetPosition;

	//現在の目的地のインデックス
	int wayPointIndex = 0;

	//移動中かどうか
	bool isMoving = false;

	//強化クリスタルのスポナー
	[SerializeField]
	PowerdStoneSpawner powerdSpowner;

	// Start is called before the first frame update
	void Start()
	{
		agent = GetComponent<NavMeshAgent>();
		StartCoroutine(OnSearchWayPoint());
	}

	IEnumerator OnSearchWayPoint()
	{
		while (true)
		{
			if (!isMoving)
			{
				isMoving = true;
				SetWayPoint();
			}
			else
			{
				//移動中であれば、十分に目的地に近づいたのち経路の再設定を行えるようにする
				if (!agent.pathPending && agent.remainingDistance < 0.5f)
				{
					isMoving = false;
				}
			}
			yield return null;
		}
	}

	//移動先を探索する
	void SetWayPoint()
	{
		//リストから目的地を選択
		targetPosition = wayPoints[wayPointIndex].position;

		//目的地と自分の高さを合わせる
		targetPosition.y = transform.position.y;

		//目的地を設定
		agent.SetDestination(targetPosition);

		//次の目的地のインデックスを設定
		//剰余算で自動的にループするように
		wayPointIndex++;
		wayPointIndex %= wayPoints.Length;
	}

	//ボーナス敵が倒されたとき強化クリスタルを生成
	public void GeneratePowerStone()
	{
		powerdSpowner.GenerarePowerdCrystal();
	}
}
