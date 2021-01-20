using UnityEngine;

//ゴーレムのアニメーションを管理
public class MeleeAnimator : MonoBehaviour
{
	//右腕のロケーター
	[SerializeField]
	GameObject rArm;

	//左腕のロケーター
	[SerializeField]
	GameObject lArm;

	//右足のロケーター
	[SerializeField]
	GameObject footRocateR;

	//左足のロケーター
	[SerializeField]
	GameObject footRocateL;

	//攻撃時のエフェクト
	[SerializeField]
	GameObject attackEffect;

	//歩きのエフェクト
	[SerializeField]
	GameObject walkEffect;

	//自身のアニメーター
	Animator anim;

	//攻撃動作中かどうか
	private bool isAttack;

	private void Awake()
	{
		anim = GetComponent<Animator>();
	}

	//攻撃のアニメーションを再生
	public void SetAttackTrigger()
	{
		if (!isAttack)
		{
			anim.SetTrigger("Attack");
		}
	}

	//歩きフラグの変更
	public void SetWalkFrag(bool frag)
	{
		anim.SetBool("isWalk", frag);
	}

	//アニメーションイベント
	public void StartAttack()
	{
		isAttack = true;
	}

	//アニメーションイベント
	public void EndAttack()
	{
		isAttack = false;
	}

	//アニメーションイベント
	public void EnableCollision()
	{
		rArm.GetComponent<BoxCollider>().enabled = true;
		lArm.GetComponent<BoxCollider>().enabled = true;
	}

	//アニメーションイベント
	public void DesableCollision()
	{
		rArm.GetComponent<BoxCollider>().enabled = false;
		lArm.GetComponent<BoxCollider>().enabled = false;
	}

	//アニメーションイベント
	public void AttackEffect()
	{
		Instantiate(attackEffect, rArm.transform);
		Instantiate(attackEffect, lArm.transform);
		MainScene.Instance.PlaySE.PlayMeleeAttackSE();
	}

	//アニメーションイベント
	public void WalkEffectR()
	{
		Instantiate(walkEffect, footRocateR.transform);
	}

	//アニメーションイベント
	public void WalkEffectL()
	{
		Instantiate(walkEffect, footRocateL.transform);
	}
}
