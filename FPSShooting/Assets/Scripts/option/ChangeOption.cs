using System.IO;
using UnityEngine;
using UnityEngine.UI;

//オプションの値変更を管理するクラス
public class ChangeOption : MonoBehaviour
{
	//オプション値の書かれたJSONファイルの格納先
	string filePath;

	//オプション値が定義されたクラス
	OptionData optionData;

	StreamWriter writer;
	StreamReader reader;

	//スライダーの配列
	[SerializeField]
	private Slider[] sliderList;

	//スライダーのハンドルの配列
	[SerializeField]
	private GameObject[] handleList;

	//オプションカテゴリー未選択時のハンドルの画像
	[SerializeField]
	Sprite knob;

	//オプションカテゴリー選択時のハンドルの画像
	[SerializeField]
	Sprite selectKnob;

	//オプション値を表示するテキストの配列
	[SerializeField]
	private Text[] numList;

	//リセットボタンの画像
	[SerializeField]
	Image resetButton;

	//リセットボタン選択フラグ
	bool reset = false;

	//リセットボタンのアニメーター
	Animator resetButtonAnim;

	//現在選ばれているスライダーを表すインデックス
	private int index;

	//水平方向のニュートラルフラグ
	bool returnNewtralHor = true;

	//垂直方向のニュートラルフラグ
	bool returnNewtralVer = true;

	//オプションのデフォルト値格納用変数
	OptionData defaultNum;

	private void Awake()
	{
		//オプションデータのインスタンス生成
		optionData = new OptionData();

		//格納先のパス設定
		filePath = Application.dataPath + "/optiondata.json";

		//JSONファイルの有無チェック
		if (!File.Exists(filePath))
		{
			CreateOptionData();
		}

		Load();
		ViewOptionValues();

		//一番上のUIを選択状態にする
		handleList[index].GetComponent<Image>().sprite = selectKnob;

		//デフォルト値をキャッシュしておく
		defaultNum = new OptionData();

		//オプション値の表示を設定
		for (int i = 0; i < sliderList.Length; i++)
		{
			numList[i].text = ": " + sliderList[i].value;
		}

		resetButtonAnim = resetButton.GetComponent<Animator>();
		resetButtonAnim.updateMode = AnimatorUpdateMode.UnscaledTime;
	}

	// Update is called once per frame
	void Update()
	{
		if (Input.GetAxisRaw("Vertical") != 0 && returnNewtralVer)
		{
			ChangeIndex();
			returnNewtralVer = false;
		}
		else if (Input.GetAxisRaw("Horizontal") != 0 && returnNewtralHor && !reset)
		{
			ChangeValue();
			returnNewtralHor = false;
		}

		//各項目の値を初期値にする
		if (Input.GetButtonDown("Submit") && reset)
		{
			Debug.Log("初期値に");
			for (int i = 0; i < sliderList.Length; i++)
			{
				sliderList[i].value = defaultNum.optionValue[i];
			}
		}

		//水平がニュートラル付近になった時
		if (Input.GetAxisRaw("Vertical") == 0)
			returnNewtralVer = true;

		//垂直がニュートラル付近になった時
		if (Input.GetAxisRaw("Horizontal") == 0)
			returnNewtralHor = true;
	}

	//ファイルがない場合、デフォルト値でオプションデータファイルを作成
	void CreateOptionData()
	{
		string jsonstr = JsonUtility.ToJson(optionData);
		writer = new StreamWriter(filePath, false);
		writer.Write(jsonstr);
		writer.Flush();
		writer.Close();
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

		JsonUtility.FromJsonOverwrite(datastr, optionData);
	}

	//更新するためのJSONデータ作成
	public OptionData CreateJson()
	{
		for (int i = 0; i < optionData.optionValue.Length; i++)
		{
			optionData.optionValue[i] = (int)sliderList[i].value;
		}

		return optionData;
	}

	//各オプションの値をテキストに表示
	private void ViewOptionValues()
	{
		for (int i = 0; i < sliderList.Length; i++)
		{
			sliderList[i].value = optionData.optionValue[i];
		}
	}

	//オプション画面退出時に設定値をセーブ
	public void SaveOptions()
	{
		Save();
	}

	//設定する項目の変更
	private void ChangeIndex()
	{
		int oldIndex = index;

		var vertical = Input.GetAxisRaw("Vertical");
		if (vertical < 0)
		{
			//リセットにフォーカスがあっている場合、一番上の項目へループ
			if (reset)
			{
				reset = false;
				index = 0;
			}
			else
			{
				index++;
				if (index > sliderList.Length - 1)
				{
					reset = true;
					index = sliderList.Length - 1;
				}
			}
		}
		else if (vertical > 0)
		{
			if (reset)
			{
				reset = false;
				index = sliderList.Length - 1;
			}
			else
			{
				index--;
				if (index < 0)
				{
					reset = true;
					index = 0;
				}
			}
		}

		//以前の項目のハンドルを非選択状態の画像へ変更
		handleList[oldIndex].GetComponent<Image>().sprite = knob;

		//リセットにフォーカスがあっていない場合、新しく選ばれた項目のハンドルを選択状態の画像へ変更
		if (reset)
			resetButtonAnim.SetBool("isSelected", true);
		else
		{
			resetButtonAnim.SetBool("isSelected", false);
			handleList[index].GetComponent<Image>().sprite = selectKnob;
		}
	}

	//各オプション値の変更
	void ChangeValue()
	{
		var horizontal = Input.GetAxisRaw("Horizontal");
		if (horizontal > 0)
		{
			if (Input.GetButton("AccelOption"))
			{
				sliderList[index].value += 10;
			}
			else
			{
				sliderList[index].value++;
			}

		}
		else if (horizontal < 0)
		{
			if (Input.GetButton("AccelOption"))
			{
				sliderList[index].value -= 10;
			}
			else
			{
				sliderList[index].value--;
			}
		}

		numList[index].text = ": " + sliderList[index].value;
	}
}
