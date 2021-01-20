//ボーナス敵の生成を管理するクラス
public class BonusEnemySpawner : Spawner
{
	//Startをオーバーライド
	void Start()
	{
		base.Spawn();
		MainScene.Instance.PlaySE.PlayQuickSpawnSE();
	}

	//スポーンさせる処理
	public void SpawnBonusEnemy()
	{
		base.Spawn();
		ShowInfo();
	}

	//メッセージ表示メソッドのオーバーライド
	void ShowInfo()
	{
		MainScene.Instance.UIController.GetInfoManager.UpdateInfo("ボーナスエネミーが再出現！");
	}
}
