using System.IO;
using UnityEngine;

//スコアを参照、保存、更新するスクリプト
public class SaveScore : MonoBehaviour
{
	//ゲームごとのスコア
	int resultScore;
	public int SetResultScore
	{
		get { return resultScore; }
		set { resultScore = value; }
	}

	//ゲームごとのクリスタル破壊数
	int resultBreakCount;
	public int SetResultBreakCount
	{
		get { return resultBreakCount; }
		set { resultBreakCount = value; }
	}

	//順位の入れ替えが発生したか
	bool isSwap = false;
	public bool GetIsSwap { get { return isSwap; } }

	//スコアデータの格納場所
	string filePath;

	ScoreData scoreData;
	StreamWriter writer;
	StreamReader reader;

	private void Awake()
	{
		scoreData = new ScoreData();
		filePath = Application.dataPath + "/scoredata.json";

		//JSONファイルの有無チェック
		if (!File.Exists(filePath))
		{
			CreateSaveData();
		}
	}

	//JSONファイルの上書き保存
	public void Save()
	{
		string jsonstr = JsonUtility.ToJson(CreateJson());
		writer = new StreamWriter(filePath, false);
		writer.Write(jsonstr);
		writer.Flush();
		writer.Close();
	}

	//JSONファイルの読み込み
	public void Load()
	{
		string datastr = "";
		reader = new StreamReader(filePath);
		datastr = reader.ReadToEnd();
		reader.Close();

		JsonUtility.FromJsonOverwrite(datastr, scoreData);
	}

	//ファイルがない場合、セーブする順位までを0で初期化しファイルを作成
	//順位数はデータクラスの配列数による
	void CreateSaveData()
	{
		for (int i = 0; i < scoreData.score.Length; i++)
		{
			scoreData.score[i] = 0;
		}
		string jsonstr = JsonUtility.ToJson(scoreData);
		writer = new StreamWriter(filePath, false);
		writer.Write(jsonstr);
		writer.Flush();
		writer.Close();
	}

	//スコアを比較し、順位の入れ替えを行う
	ScoreData SwapRank()
	{
		Debug.Log(scoreData.score.Length);
		for (int i = 0; i < scoreData.score.Length; i++)
		{
			if (scoreData.score[i] < resultScore)
			{
				isSwap = true;

				var tmp = scoreData.score[i];
				scoreData.score[i] = resultScore;
				if (i + 1 < scoreData.score.Length)
				{
					scoreData.score[i + 1] = tmp;
					Debug.Log((i + 2) + "位に" + tmp + "点を格納");
				}
				break;
			}
		}
		return scoreData;
	}

	//更新するためのJSONデータ作成
	ScoreData CreateJson()
	{
		Load();
		scoreData = SwapRank();
		scoreData.resultScore = resultScore;
		scoreData.breakCount = resultBreakCount;
		scoreData.isSwap = isSwap;

		return scoreData;
	}
}
