using UnityEngine;
using UnityEngine.SceneManagement;

//ランキングシーンを管理するクラス
public class RankingScene : MonoBehaviour
{
	void Update()
	{
		if (Input.GetButtonDown("Cancel"))
		{
			SceneManager.LoadScene("clear");
		}
	}
}
