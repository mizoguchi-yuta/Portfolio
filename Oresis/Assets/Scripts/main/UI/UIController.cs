using UnityEngine;

//UI全体を管理するクラス
public class UIController : MonoBehaviour
{
	//UI生成のルートになるキャンバス
	[SerializeField]
	private Canvas canvasRoot;

	//制限時間管理クラスが割り当てられているゲームオブジェクト
	[SerializeField]
	private GameObject timePrefab;
	//制限時間を管理するクラス
	private TimeManager timeManager;
	public TimeManager GetTimeManager
	{
		get { return timeManager; }
	}


	//スコア管理クラスが割り当てられているゲームオブジェクト
	[SerializeField]
	private GameObject scorePrefab;
	//スコアを管理するクラス
	private ScoreManager scoreManager;
	public ScoreManager GetScoreManager
	{
		get { return scoreManager; }
	}

	//情報表示管理クラスが割り当てられているゲームオブジェクト
	[SerializeField]
	private GameObject infoPrefab;
	//情報表示を管理するクラス
	private InfoManager infoManager;
	public InfoManager GetInfoManager
	{
		get { return infoManager; }
	}

	//クリア時のフェードを管理するクラス
	[SerializeField]
	private FadeManager fadeManager;
	public FadeManager GetFadeManager
	{
		get { return fadeManager; }
	}

	//ポーズUI管理クラスが割り当てられているゲームオブジェクト
	[SerializeField]
	private GameObject PausePrefab;
	//ポーズのUIを管理するクラス
	private PauseManager pauseManager;
	public PauseManager GetPauseManager
	{
		get { return pauseManager; }
	}

	void Start()
	{
		//各UIのプレハブを生成し、キャンバスルートを設定
		timeManager = Instantiate(timePrefab, canvasRoot.transform).GetComponent<TimeManager>();
		timeManager.CanvasRoot = canvasRoot;

		scoreManager = Instantiate(scorePrefab, canvasRoot.transform).GetComponent<ScoreManager>();
		scoreManager.CanvasRoot = canvasRoot;

		infoManager = Instantiate(infoPrefab, canvasRoot.transform).GetComponent<InfoManager>();
		infoManager.CanvasRoot = canvasRoot;

		fadeManager.CanvasRoot = canvasRoot;
	}

	//ポーズ画面のUIを生成
	public void CreatePauseUI()
	{
		pauseManager = Instantiate(PausePrefab, canvasRoot.transform).GetComponent<PauseManager>();
	}
}
