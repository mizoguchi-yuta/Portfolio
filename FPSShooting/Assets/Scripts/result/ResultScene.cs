using UnityEngine;
using UnityEngine.SceneManagement;

//リザルトシーンを管理するクラス
public class ResultScene : MonoBehaviour
{
	//メニューを格納する配列
	[SerializeField]
	private GameObject[] menu;

	//選ばれているメニューを表すインデックス
	int index = 0;

	//スコア取得、入れ替えを行うクラス
	[SerializeField]
	private PrevScore prevScore;

	//クラス格納用変数
	[SerializeField]
	private PlaySE playSE;

	//Axis入力がニュートラルに戻ったか
	bool returnNewtral = true;

	private void Start()
	{
		menu[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	// Update is called once per frame
	void Update()
	{
		if (Input.GetAxisRaw("Horizontal") != 0 && returnNewtral)
		{
			returnNewtral = false;
			playSE.PlayCursorSE();
			changeIndex();
		}
		else if (Input.GetButtonDown("Submit"))
		{
			playSE.PlaySubmitSE();
			submitStage();
		}

		//スティックがニュートラル付近になった時
		if (Input.GetAxisRaw("Horizontal") == 0)
			returnNewtral = true;
	}

	//選択項目の移動
	void changeIndex()
	{
		int oldIndex = index;

		var horizontal = Input.GetAxisRaw("Horizontal");

		#region//左右入力
		if (horizontal > 0)
		{
			index++;
			if (index > 1)
				if (index > menu.Length - 1)
				{
					index = 0;
				}
		}
		else if (horizontal < 0)
		{
			index--;
			if (index < 0)
			{
				index = menu.Length - 1;
			}
		}
		#endregion

		menu[oldIndex].GetComponent<Animator>().SetBool("isSelected", false);
		menu[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	//項目の決定
	void submitStage()
	{
		switch (index)
		{
			case 0:
				SceneManager.LoadScene("main");
				break;
			case 1:
				SceneManager.LoadScene("ranking");
				break;
			case 2:
				SceneManager.LoadScene("title");
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
