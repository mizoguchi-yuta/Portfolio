using UnityEngine;
using UnityEngine.UI;

//ポーズ中のUIを管理するクラス
public class PauseManager : MonoBehaviour
{
	//ポーズテキスト
	[SerializeField]
	private Text pauseText;

	//選択できるメニューを格納する配列
	[SerializeField]
	private GameObject[] menuList;

	//オプション選択時に表示するプレハブ
	private GameObject OptionWindow;

	//オプションの値の取得、保存を行うクラス
	private ChangeOption changeOption;

	//ポーズ中に表示する背景
	private Image pauseImage;

	//選択されているメニューを表すインデックス
	int index = 0;

	//オプション画面を開いているかどうか
	bool isOption = false;

	//左右入力がニュートラルに戻ったか
	bool returnNewtral = true;

	void Start()
	{
		//ポーズ画面は最前面に
		transform.SetAsLastSibling();
		Time.timeScale = 0;
		pauseImage = GetComponent<Image>();

		for (int i = 0; i < menuList.Length; i++)
		{
			//各メニューのアニメーションをタイムスケールの影響を受けないよう設定
			menuList[i].GetComponent<Animator>().updateMode = AnimatorUpdateMode.UnscaledTime;
		}

		menuList[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	void Update()
	{
		//オプション画面を開いていない場合は、ポーズメニューの選択、決定を行う
		if (!isOption)
		{
			if (Input.GetAxisRaw("Vertical") != 0 && returnNewtral)
			{
				ChangeIndex();
				returnNewtral = false;
			}
			else if (Input.GetButtonDown("Submit"))
			{
				submitMenu();
			}
		}
		else
		{
			if (Input.GetButtonDown("Cancel"))
			{
				CloseOptionWindow();
			}
		}

		//スティックの垂直入力がニュートラルになった時
		if (Input.GetAxisRaw("Vertical") == 0)
			returnNewtral = true;
	}

	//メニューの選択
	void ChangeIndex()
	{
		int oldIndex = index;

		var vertical = Input.GetAxisRaw("Vertical");
		if (vertical < 0)
		{
			index++;
			if (index > menuList.Length - 1)
			{
				index = 0;
			}
		}
		else if (vertical > 0)
		{
			index--;
			if (index < 0)
			{
				index = menuList.Length - 1;
			}
		}

		//以前のメニューを非選択、新しく選ばれたメニューを選択状態に
		menuList[oldIndex].GetComponent<Animator>().SetBool("isSelected", false);
		menuList[index].GetComponent<Animator>().SetBool("isSelected", true);
	}

	//メニューの決定
	void submitMenu()
	{
		switch (index)
		{
			case 0:
				ReturnGame();
				break;
			case 1:
				CreateOptionWindow();
				break;
			case 2:
				Time.timeScale = 1;
				MainScene.Instance.ReturnTitle();
				break;
		}
	}

	//ゲームに戻る
	void ReturnGame()
	{
		MainScene.Instance.IsPause = false;
		Time.timeScale = 1;
		Destroy(this.gameObject);
	}

	//オプション画面の生成
	void CreateOptionWindow()
	{
		//ポーズ画面のUIを非表示
		ChangeVisiblePauseUI(false);

		//オプション状態フラグをオン
		isOption = true;

		//オプションウィンドウを生成
		OptionWindow = Instantiate((GameObject)Resources.Load("OptionWindow"), MainScene.Instance.GetCanvasRoot);
		changeOption = OptionWindow.GetComponent<ChangeOption>();
	}

	//ポーズメニューの表示非表示を変更
	void ChangeVisiblePauseUI(bool isVisible)
	{
		for (int i = 0; i < menuList.Length; i++)
		{
			menuList[i].SetActive(isVisible);
		}
	}

	//オプション画面を閉じたときの処理
	public void CloseOptionWindow()
	{
		//オプション値を保存
		changeOption.SaveOptions();

		//オプション値を更新
		MainScene.Instance.GetOptionManager.SetOptionValue();

		//オプションウィンドウのプレハブを破棄
		Destroy(OptionWindow);

		//オプション状態フラグをオフ
		isOption = false;

		//ポーズ画面のUIを表示
		ChangeVisiblePauseUI(true);
	}
}
