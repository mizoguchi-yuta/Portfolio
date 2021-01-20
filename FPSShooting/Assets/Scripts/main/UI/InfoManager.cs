using UnityEngine;
using UnityEngine.UI;

//要点で出現するメッセージを管理するクラス
public class InfoManager : MonoBehaviour
{
	//表示したいメッセージ内容
	[SerializeField]
	private Text infoText;

	//メッセージを生成するキャンバスのルート
	private Canvas canvasRoot;
	public Canvas CanvasRoot
	{
		set { canvasRoot = value; }
	}

	void Start()
	{
		UpdateInfo("スコアを稼げ！");
	}

	//メッセージ内容を設定して表示
	public void UpdateInfo(string message)
	{
		MainScene.Instance.PlaySE.PlayInfoSE();
		infoText.text = message;
		GetComponent<Animator>().SetTrigger("showInfo");
	}
}
