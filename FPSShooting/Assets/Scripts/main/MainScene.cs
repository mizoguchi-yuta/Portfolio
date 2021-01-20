using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

//プレイシーン全体を管理するクラス
public class MainScene : MonoBehaviour
{
	//カメラオブジェクトを定義
	[SerializeField]
	private Camera mainCamera;
	public Camera GetMainCamera
	{
		get { return mainCamera; }
	}

	//UI生成のルートになるキャンバスを定義
	[SerializeField]
	private Transform canvasRoot;
	public Transform GetCanvasRoot
	{
		get { return canvasRoot; }
	}

	//プレイヤーオブジェクトを定義
	[SerializeField]
	private GameObject player;

	//プレイヤーオブジェクトのプロパティ
	public GameObject GetPlayer { get { return player; } }

	//SEマネージャーからSE再生のクラスを取得
	[SerializeField]
	private PlaySE playSE;
	public PlaySE PlaySE
	{
		get { return playSE; }
	}

	//UIマネージャーからUI操作のクラスを取得
	[SerializeField]
	private UIController uiController;
	public UIController UIController
	{
		get { return uiController; }
	}

	//オプションマネージャーからオプション値設定用クラスを取得
	[SerializeField]
	private OptionManager optionManager;
	public OptionManager GetOptionManager
	{
		get { return optionManager; }
	}

	//スコアの保存用スクリプト
	[SerializeField]
	private SaveScore saveScore;

	//ポーズ状態かどうか
	private bool isPause;
	public bool IsPause
	{
		get { return isPause; }
		set { isPause = value; }
	}

	//オプション設定中かどうか
	private bool isOption;
	public bool IsOption
	{
		get { return isOption; }
		set { isOption = value; }
	}

	//通常クリスタルを破壊した数
	int breakCount = 0;

	#region インスタンスへのstaticなアクセスポイント
	// このクラスのインスタンスを取得します。
	public static MainScene Instance
	{
		get { return instance; }
		set { instance = value; }
	}
	private static MainScene instance = null;

	// AwakeメソッドはStartメソッドよりも先に実行したい初期化処理を記述します。
	void Awake()
	{
		// 生成されたインスタンス（自分自身）をstaticな変数に保存
		instance = this;
	}
	#endregion

	// Start is called before the first frame update
	void Start()
	{
		//マウスポインターを非表示に
		Cursor.lockState = CursorLockMode.Locked;
		Cursor.visible = false;
	}

	// Update is called once per frame
	void Update()
	{
		//ポーズボタンを押した時
		if (Input.GetButtonDown("Pause") && !isPause)
		{
			isPause = true;

			//ポーズのUIを生成
			uiController.CreatePauseUI();
		}
	}

	//クリスタルの破壊数を加算
	public void AddBreakCount()
	{
		breakCount++;
	}

	//クリア時の処理
	public void Clear()
	{
		int score = uiController.GetScoreManager.Score;
		saveScore.SetResultScore = score;
		saveScore.SetResultBreakCount = breakCount;
		saveScore.Save();
		StartCoroutine(OnClear());
	}

	//クリア時の演出を行うコルーチン
	IEnumerator OnClear()
	{
		playSE.PlayFadeSE();
		uiController.GetFadeManager.CreateFadePrefab();
		Time.timeScale = 0.1f;
		yield return new WaitForSeconds(0.5f);
		Time.timeScale = 1.0f;
		yield return new WaitForSeconds(0.5f);
		SceneManager.LoadScene("clear");
	}

	//タイトルへ戻る処理
	public void ReturnTitle()
	{
		SceneManager.LoadScene("title");
	}
}
