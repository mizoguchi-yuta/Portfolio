using UnityEngine;
using UnityEngine.SceneManagement;

//タイトルシーンを管理するクラス
public class TitleScene : MonoBehaviour
{
	//メニューを格納する配列
	[SerializeField]
	GameObject[] menu;

	//選ばれているメニューを表すインデックス
	int index = 0;

	//クラス格納用変数
	[SerializeField]
	private PlaySE playSE;
	public PlaySE PlaySE
	{
		get { return playSE; }
	}

	//Axis入力がニュートラルに戻ったか
	bool returnNewtral = true;

	#region インスタンスへのstaticなアクセスポイント
	// このクラスのインスタンスを取得します。
	public static TitleScene Instance
	{
		get { return instance; }
		set { instance = value; }
	}
	private static TitleScene instance = null;

	// AwakeメソッドはStartメソッドよりも先に実行したい初期化処理を記述します。
	void Awake()
	{
		// 生成されたインスタンス（自分自身）をstaticな変数に保存
		instance = this;
	}
	#endregion

	private void Start()
	{
		menu[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	private void Update()
	{
		if (Input.GetAxisRaw("Vertical") != 0 && returnNewtral)
		{
			returnNewtral = false;
			playSE.PlayCursorSE();
			ChangeIndex();
		}
		else if (Input.GetButtonDown("Submit"))
		{
			playSE.PlaySubmitSE();
			SubmitStage();
		}

		//スティックがニュートラル付近になった時
		if (Input.GetAxisRaw("Vertical") == 0)
			returnNewtral = true;
	}

	//選択項目の移動
	void ChangeIndex()
	{
		int oldIndex = index;

		var vertical = Input.GetAxisRaw("Vertical");

		#region//上下入力
		if (vertical < 0)
		{
			index++;
			if (index > menu.Length - 1)
			{
				index = 0;
			}
		}
		else if (vertical > 0)
		{
			index--;
			if (index < 0)
			{
				index += menu.Length;
			}
		}
		#endregion

		menu[oldIndex].GetComponent<Animator>().SetBool("isSelected", false);
		menu[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	//項目の決定
	void SubmitStage()
	{
		switch (index)
		{
			case 0:
				SceneManager.LoadScene("main");
				break;
			case 1:
				SceneManager.LoadScene("tutorial");
				break;
			case 2:
				SceneManager.LoadScene("option");
				break;
			case 3:
#if UNITY_EDITOR
				UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_STANDALONE
      UnityEngine.Application.Quit();
#endif
				break;
		}
	}
}