using System.IO;
using UnityEngine;
using UnityEngine.UI;

//リザルトのスコア表示を行うスクリプト
public class PrevScore : MonoBehaviour
{
	//破壊数表示テキスト
	[SerializeField]
	private Text BreakCountText;

	//スコア表示用テキスト
	[SerializeField]
	private Text scoreText;

	//ランクインしたかのテキスト
	[SerializeField]
	private GameObject rankInText;

	//クラス格納用変数
	[SerializeField]
	SpawnBreakCrystal spawnBreakCrystal;

	//クラス格納用変数
	ScoreData scoreData;

	//JSONファイル格納先パス
	string filePath;

	private void Start()
	{
		LoadJSON();

		//破壊した数のテキストに今回の破壊数を表示
		BreakCountText.text = scoreData.breakCount.ToString();

		//スコアのテキストに今回のスコアを表示
		scoreText.text = scoreData.resultScore.ToString();

		//スコアの入れ替えがあった場合は、ランクインの表示を有効化する
		if (scoreData.isSwap)
		{
			rankInText.SetActive(true);
		}

		//破壊した数だけクリスタルを生成
		spawnBreakCrystal.startSpawn(scoreData.breakCount);
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
