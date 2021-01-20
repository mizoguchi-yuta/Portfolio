using UnityEngine;

//SE再生を管理するクラス
public class PlaySE : MonoBehaviour
{
	//SEをまとめているスクリプタブルオブジェクト
	private SEList seList;

	private AudioSource source;

	void Start()
	{
		seList = Resources.Load<SEList>("SEList");
		source = GetComponent<AudioSource>();
	}

	public void PlayCursorSE()
	{
		source.PlayOneShot(seList.cursorSE);
	}

	public void PlaySubmitSE()
	{
		source.PlayOneShot(seList.submitSE);
	}

	public void PlayInfoSE()
	{
		source.PlayOneShot(seList.infoSE);
	}

	public void PlayFadeSE()
	{
		source.PlayOneShot(seList.fadeSE);
	}

	public void PlayEnemyHitSE()
	{
		source.PlayOneShot(seList.enemyHitSE);
	}

	public void PlayBreakSE()
	{
		source.PlayOneShot(seList.BreakSE);
	}

	public void PlayEnemyEatSE()
	{
		source.PlayOneShot(seList.EnemyEatSE);
	}

	public void PlayImpactSE()
	{
		source.PlayOneShot(seList.ImpactSE);
	}

	public void PlayMeleeAttackSE()
	{
		source.PlayOneShot(seList.MeleeAttackSE);
	}

	public void PlayPowerdBreakSE()
	{
		source.PlayOneShot(seList.PowerdBreakSE);
	}

	public void PlayPowerUpSE()
	{
		source.PlayOneShot(seList.PowerUpSE);
	}

	public void PlayQuickSpawnSE()
	{
		source.PlayOneShot(seList.QuickSpawnSE);
	}

	public void PlayEnemySpawnSE()
	{
		source.PlayOneShot(seList.EnemySpawnSE);
	}

	public void PlayWeaponHitSE()
	{
		source.PlayOneShot(seList.WeaponHitSE);
	}
}
