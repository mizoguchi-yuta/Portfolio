using System.IO;
using UnityEngine;

//オプション画面を管理するクラス
public class OptionManager : MonoBehaviour
{
	//カメラ感度を適用するスクリプト
	[SerializeField]
	private TPSCamera tpsCamera;

	//音量を適用するスクリプト
	[SerializeField]
	private SoundManager soundManager;

	//オプション値が書かれたJSONファイルの出力先
	string filePath;

	OptionData optionData;
	StreamReader reader;

	//オプション値の更新
	public void SetOptionValue()
	{
		Load();
		tpsCamera.SetCameraSpeed(optionData.optionValue[0]);
		soundManager.SetVolume(optionData.optionValue[1], optionData.optionValue[2]);
	}

	//JSONファイルの読み込み
	public void Load()
	{
		optionData = new OptionData();
		filePath = Application.dataPath + "/optiondata.json";
		string datastr = "";
		reader = new StreamReader(filePath);
		datastr = reader.ReadToEnd();
		reader.Close();

		JsonUtility.FromJsonOverwrite(datastr, optionData);
	}
}
