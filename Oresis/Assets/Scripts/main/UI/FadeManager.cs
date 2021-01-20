using UnityEngine;

//ゲーム終了時のフェードを管理するクラス
public class FadeManager : MonoBehaviour
{
	//フェードを生成するキャンバスのルート
	private Canvas canvasRoot;
	public Canvas CanvasRoot
	{
		set { canvasRoot = value; }
	}

	//生成するフェードプレハブ
	private GameObject fadePrefab;

	private void Start()
	{
		fadePrefab = (GameObject)Resources.Load("Fade");
	}

	public void CreateFadePrefab()
	{
		MainScene.Instance.PlaySE.PlayFadeSE();
		Instantiate(fadePrefab, canvasRoot.transform);
	}
}
