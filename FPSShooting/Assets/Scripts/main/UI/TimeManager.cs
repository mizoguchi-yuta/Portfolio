using UnityEngine;
using UnityEngine.UI;

//ゲームの制限時間を管理するクラス
public class TimeManager : MonoBehaviour
{
	//秒数の設定用変数
	[SerializeField]
	private float minute;

	//分数の設定用変数
	[SerializeField]
	private float seconds;

	//合計時間(秒)
	private float currentTime;

	//前フレームの合計時間(秒)
	private float oldSeconds;

	//最大時間(秒)
	float maxTime;

	//分数の表示用テキスト
	[SerializeField]
	private Text minuteText;

	//秒数の表示用テキスト
	[SerializeField]
	private Text secondText;

	//時間減少時に表示するUIのプレハブ
	[SerializeField]
	GameObject decPrefab;

	//一度制限時間が0になったか
	bool isZero = false;

	//UIを生成するキャンバスのルート
	private Canvas canvasRoot;
	public Canvas CanvasRoot
	{
		set { canvasRoot = value; }
	}

	// Start is called before the first frame update
	void Start()
	{
		maxTime = minute * 60 + seconds;
		currentTime = maxTime;
		oldSeconds = 0f;
		UpdateTime();
	}

	// Update is called once per frame
	void Update()
	{
		CountDown();
	}

	void CountDown()
	{
		//　制限時間以下になったら終了
		if (currentTime <= 0f)
		{
			if (!isZero)
			{
				isZero = true;
				minuteText.text = "00";
				secondText.text = "00";
				MainScene.Instance.Clear();
			}
		}
		else
		{
			UpdateTime();
			currentTime -= Time.deltaTime;

			//　タイマー表示用UIテキストに時間を表示する
			if ((int)seconds != (int)oldSeconds)
			{
				minuteText.text = minute.ToString("0");
				secondText.text = ((int)seconds).ToString("00");
			}
			oldSeconds = seconds;
		}
	}

	//時間減少UIの生成
	public void DecTime(float damage, Vector3 playerPos)
	{
		var decText = Instantiate(decPrefab, canvasRoot.transform);
		decText.GetComponentInChildren<Text>().text = "-" + damage + "s";
		decText.GetComponent<RectTransform>().position = RectTransformUtility.WorldToScreenPoint(Camera.main, new Vector3(playerPos.x, playerPos.y + 3, playerPos.z));

		currentTime -= damage;
	}

	//制限時間の再設定
	void UpdateTime()
	{
		minute = (int)currentTime / 60;
		seconds = currentTime - minute * 60;
	}
}
