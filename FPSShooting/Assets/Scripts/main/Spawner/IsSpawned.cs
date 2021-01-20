//敵やクリスタルの生成位置に持たせ、すでに存在しているかを表す
public class IsSpawned
{
	bool isSpawn = false;
	public bool GetIsSpawn
	{
		get { return isSpawn; }
		set { isSpawn = value; }
	}
}
