using UnityEngine;

public class PlayerAnimation : MonoBehaviour
{
	//武器の判定がついたオブジェクト
	[SerializeField]
	private GameObject weapon;

	//プレイヤーのルートオブジェクト
	[SerializeField]
	private GameObject playerRoot;
	private PlayerMove playerMove;

	//プレイヤーのアニメーターがついたオブジェクト
	private Animator playerAnimator;

	//プレイヤーの接触判定クラス
	[SerializeField]
	HitObjectPlayer hitObjectPlayer;

	//ダメージ時の気絶エフェクト
	[SerializeField]
	GameObject stanEffect;

	//エフェクト発生の基点
	[SerializeField]
	Transform effectRoot;

	//移動速度を格納する変数
	Vector3 moveDirection;

	//攻撃中かどうか
	bool isAttacking = false;

	//怯み中かどうか
	bool isStan = false;

	private void Start()
	{
		playerMove = playerRoot.GetComponent<PlayerMove>();
		playerAnimator = GetComponent<Animator>();
	}

	private void Update()
	{
		moveDirection = playerMove.GetMovceDirection;
		ChangeAnimation(moveDirection.x, moveDirection.z);
	}

	//アニメーションの切り替え
	void ChangeAnimation(float x, float z)
	{
		if (x != 0 || z != 0)
		{
			playerAnimator.SetBool("isRunning", true);
		}
		else
		{
			playerAnimator.SetBool("isRunning", false);
		}

		if (Input.GetButtonDown("Fire1"))
		{
			if (!isAttacking)
			{
				playerAnimator.SetTrigger("Attack");
			}
		}
	}

	public void IsDamage()
	{
		//怯んでいないならダメージモーション再生
		if (!isStan)
		{
			playerAnimator.SetTrigger("Damage");
		}
	}

	#region //アニメーションイベント
	//武器のコリジョンの有効化
	public void EnableCollision()
	{
		weapon.GetComponent<BoxCollider>().enabled = true;
	}

	//武器のコリジョンの無効化
	public void DesableCollision()
	{
		weapon.GetComponent<BoxCollider>().enabled = false;
	}

	//攻撃中フラグをオン
	public void StartAttack()
	{
		//攻撃中無敵付与
		hitObjectPlayer.SetIsInvincible = true;
		isAttacking = true;
	}

	//攻撃中フラグをオフ
	public void EndAttack()
	{
		//攻撃中無敵解除
		hitObjectPlayer.SetIsInvincible = true;
		isAttacking = false;
	}

	//無敵の有効化
	public void EnableInvinsible()
	{
		hitObjectPlayer.SetIsInvincible = true;
		isStan = true;
		Instantiate(stanEffect, effectRoot);
	}

	//無敵の無効化
	public void DesableInvinsible()
	{
		hitObjectPlayer.SetIsInvincible = false;
		isStan = false;
	}
	#endregion
}
