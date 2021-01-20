using System.Collections;
using UnityEngine;
using UnityEngine.AI;

//ゴーレムの動きを管理するクラス
public class AI_MeleeEnemy : MonoBehaviour
{
	//ナビメッシュエージェントを取得
	private NavMeshAgent agent;

	//目標物の位置を格納
	Vector3 targetPosition;

	//徘徊時の移動先リスト
	[SerializeField]
	private Transform[] wayPointList;

	//プレイヤーを見つけたかどうか
	bool findPlayer = false;

	//ゴーレムのアニメーター
	[SerializeField]
	MeleeAnimator meleeAnim;

	private void Start()
	{
		agent = GetComponent<NavMeshAgent>();
		agent.SetDestination(wayPointList[Random.Range(0, wayPointList.Length)].position);
		StartCoroutine(MoveTarget());
	}

	private void OnTriggerStay(Collider other)
	{
		if (other.gameObject.tag == "Player")
		{
			findPlayer = true;
			//プレイヤーが探索範囲にいる間は追いかける
			agent.SetDestination(other.gameObject.transform.position);
		}
	}

	private void OnTriggerExit(Collider other)
	{
		//プレイヤーが監視範囲から外れた場合は発見フラグをオフ
		findPlayer = false;
	}

	//目標物へと移動するコルーチン
	IEnumerator MoveTarget()
	{
		while (true)
		{
			//プレイヤーを未発見の場合
			if (!findPlayer)
			{
				//速度で歩きのアニメーションを変更
				if (agent.velocity.magnitude > 0)
					meleeAnim.SetWalkFrag(true);
				else
					meleeAnim.SetWalkFrag(false);

				//十分に近づいたら目的地を再設定
				if (!agent.pathPending && agent.remainingDistance < 0.5f)
					agent.SetDestination(wayPointList[Random.Range(0, wayPointList.Length)].position);
			}
			else
			{
				//プレイヤーに一定以上近づいた場合攻撃
				if (agent.remainingDistance < 25.0f)
				{
					meleeAnim.SetWalkFrag(false);
					meleeAnim.SetAttackTrigger();
				}
			}
			yield return null;
		}
	}
}
