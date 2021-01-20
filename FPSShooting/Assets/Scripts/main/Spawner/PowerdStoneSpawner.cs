//強化クリスタルの生成クラス
public class PowerdStoneSpawner : Spawner
{
	//生成実行
	public void GenerarePowerdCrystal()
	{
		base.Spawn();
		SetSpawner();
		ShowInfo();
	}

	//メッセージ表示メソッドのオーバーライド
	void ShowInfo()
	{
		MainScene.Instance.UIController.GetInfoManager.UpdateInfo("強化クリスタルが出現！");
	}

	//生成した強化クリスタルの位置を登録
	void SetSpawner()
	{
		var breakCrystal = spawnObject.GetComponent<BreakCrystal>();
		if (breakCrystal != null)
		{
			breakCrystal.SetSpawner = gameObject;
		}
	}
}
