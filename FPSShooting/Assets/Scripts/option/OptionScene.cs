using UnityEngine;
using UnityEngine.SceneManagement;

//オプションのシーンを管理するクラス
public class OptionScene : MonoBehaviour
{
	//オプションの変更を管理するクラス
	[SerializeField]
	ChangeOption changeOption;

	void Update()
	{
		if (Input.GetButtonDown("Cancel"))
		{
			changeOption.SaveOptions();
			SceneManager.LoadScene("title");
		}
	}
}
