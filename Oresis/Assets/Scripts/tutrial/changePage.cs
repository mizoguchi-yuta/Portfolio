using UnityEngine;
using UnityEngine.SceneManagement;

//チュートリアルのページ変更を管理するクラス
public class ChangePage : MonoBehaviour
{
	//チュートリアルの各画像を格納するリスト
	[SerializeField]
	GameObject[] pageList;

	//選ばれているページのインデックス
	int index = 0;

	//Axis入力がニュートラルに戻ったか
	bool returnNewtral = true;

	void Update()
	{
		if (Input.GetAxisRaw("Horizontal") != 0 && returnNewtral)
		{
			returnNewtral = false;
			ChangeIndex();
		}

		//キャンセルボタンが押されたらタイトルへ
		if (Input.GetButtonDown("Cancel"))
		{
			SceneManager.LoadScene("title");
		}

		//スティックがニュートラル付近になった時
		if (Input.GetAxisRaw("Horizontal") == 0)
			returnNewtral = true;
	}

	//ページめくり
	void ChangeIndex()
	{
		int oldIndex = index;

		var horizontal = Input.GetAxisRaw("Horizontal");

		#region//左右入力
		if (horizontal > 0)
		{
			index++;
			if (index > 1)
				if (index > pageList.Length - 1)
				{
					index = pageList.Length - 1;
				}
		}
		else if (horizontal < 0)
		{
			index--;
			if (index < 0)
			{
				index = 0;
			}
		}
		#endregion

		pageList[oldIndex].SetActive(false);
		pageList[index].SetActive(true);
	}
}
