using UnityEngine;

//プレイヤーが特定のオブジェクトにヒットした際の処理
public class HitObjectPlayer : MonoBehaviour
{
	//プレイヤーのアニメーター
	[SerializeField]
	PlayerAnimation playerAnimation;

	//無敵状態かどうかのフラグ
	[SerializeField]
	bool isInvincible = false;
	public bool SetIsInvincible
	{
		set { isInvincible = value; }
	}

	private void OnCollisionEnter(Collision collision)
	{

		//敵にヒットした時
		if (collision.gameObject.CompareTag("Enemy") && !isInvincible)
		{
			Debug.Log(collision.gameObject.name);
			playerAnimation.IsDamage();
			MainScene.Instance.UIController.GetTimeManager.DecTime(10, transform.position);
		}
	}

	private void OnTriggerEnter(Collider other)
	{
		//近接敵の攻撃にヒットした時
		if (other.gameObject.CompareTag("Melee") && !isInvincible)
		{
			isInvincible = true;
			playerAnimation.IsDamage();
			MainScene.Instance.UIController.GetTimeManager.DecTime(30, transform.position);
			Debug.Log("ゴーレムの攻撃を受けました");
		}
	}
}
