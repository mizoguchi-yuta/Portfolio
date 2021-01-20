using UnityEngine;

//SEをまとめるスクリプタブルオブジェクト
[CreateAssetMenu(menuName = "MyScriptable/Create SEInfo")]
public class SEList : ScriptableObject
{
	public AudioClip cursorSE;

	public AudioClip submitSE;

	public AudioClip infoSE;

	public AudioClip fadeSE;

	public AudioClip enemyHitSE;

	public AudioClip BreakSE;

	public AudioClip EnemyEatSE;

	public AudioClip ImpactSE;

	public AudioClip MeleeAttackSE;

	public AudioClip PowerdBreakSE;

	public AudioClip PowerUpSE;

	public AudioClip QuickSpawnSE;

	public AudioClip EnemySpawnSE;

	public AudioClip WeaponHitSE;

	public AudioClip CrystalSpawnSE;
}
