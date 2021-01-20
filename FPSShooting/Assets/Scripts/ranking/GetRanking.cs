using System.IO;
using UnityEngine;
using UnityEngine.UI;

//ランキングとしてセーブされたスコアを取得するクラス
public class GetRanking : MonoBehaviour
{
	//順位ごとのスコアを表示するテキスト
	[SerializeField]
	private Text[] scoreText;

	//スコアデータのクラス
	ScoreData scoreData;

	//JSONファイルの格納先パス
	string filePath;

	void Start()
	{
		LoadJSON();
		for (int i = 0; i < scoreData.score.Length; i++)
		{
			scoreText[i].text = scoreData.score[i].ToString();
		}
	}

	//JSONファイル読み込み
	void LoadJSON()
	{
		filePath = Application.dataPath + "/scoredata.json";

		scoreData = new ScoreData();
		string datastr = "";
		StreamReader reader;
		reader = new StreamReader(filePath);
		datastr = reader.ReadToEnd();
		reader.Close();

		JsonUtility.FromJsonOverwrite(datastr, scoreData);
	}
}
