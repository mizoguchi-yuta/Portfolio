using System.Collections;
using UnityEngine;
using UnityEngine.UI;

//チェイン(コンボ)を管理するクラス
public class Chain : MonoBehaviour
{
	//チェイン数を表示するテキスト
	[SerializeField]
	private Text chainText;

	//倍率を表示するテキスト
	[SerializeField]
	private Text magnificationText;

	//チェイン時間ゲージのイメージ
	[SerializeField]
	private Image chainGauge;

	//チェイン時間ゲージの背景
	[SerializeField]
	private Image chainGaugeBG;

	//チェインの制限時間
	[SerializeField]
	private float chainLimit;

	//チェイン数
	private float chainCount = 0;

	//チェイン中の取得スコア
	private float chainScore;

	//チェインの残り時間
	private float remainingChainTime;

	//チェイン中かどうか
	private bool isChain;

	//チェインの時間計測コルーチンを格納する変数
	private IEnumerator onChain;

	// Start is called before the first frame update
	void Start()
	{
		//チェインの残り時間に最大値をセット
		remainingChainTime = chainLimit;
		//コルーチンをセット
		onChain = OnChain();
	}

	//チェインの開始
	void StartChain()
	{
		//チェイン状態フラグをオン
		isChain = true;

		//チェインゲージの可視化
		chainGauge.enabled = true;
		chainGaugeBG.enabled = true;

		UpdateText();
	}

	//チェイン数の加算
	public void AddChain(Vector3 crystalPos)
	{
		chainCount++;

		//チェインが始まっている時
		if (isChain)
		{
			//コンボ数を更新
			UpdateText();
			//得点の基礎値にチェイン倍率を掛けたスコアを加算
			MainScene.Instance.UIController.GetScoreManager.UpdateScore(Mathf.RoundToInt(100 * float.Parse(chainScore.ToString("f2"))), crystalPos);
			//時間制限のコルーチンをリセット
			ResetCoroutine();
		}
		//チェインしていない時
		else
		{
			//得点の基礎値のみスコアに加算
			MainScene.Instance.UIController.GetScoreManager.UpdateScore(100, crystalPos);
		}

		//チェインが始まっていない状態で2つめのクリスタルを壊した場合、チェインの計測を開始
		if (chainCount >= 2 && !isChain)
		{
			StartChain();
			StartCoroutine(onChain);
		}
	}

	//UIの表示をアップデート
	void UpdateText()
	{
		chainText.text = chainCount + " Chain！";
		chainScore = 1 + ((chainCount - 1) / 10);
		magnificationText.text = "x" + chainScore;
	}

	//チェイン有効時間を延長
	void ResetCoroutine()
	{
		remainingChainTime = chainLimit;
		StopCoroutine(onChain);
		onChain = OnChain();
		StartCoroutine(onChain);
	}

	//チェイン状態を解除
	void ResetChain()
	{
		isChain = false;

		remainingChainTime = chainLimit;
		StopCoroutine(onChain);
		onChain = OnChain();

		chainText.text = "";
		magnificationText.text = "";

		chainGauge.enabled = false;
		chainGaugeBG.enabled = false;

		chainCount = 0;
	}

	//チェイン時間を計るコルーチン
	IEnumerator OnChain()
	{
		while (true)
		{
			remainingChainTime -= Time.deltaTime;

			//ゲージの減少
			var currentGauge = remainingChainTime / chainLimit;
			chainGauge.fillAmount = currentGauge;

			if (remainingChainTime <= 0)
			{
				ResetChain();
				yield break;
			}
			yield return null;
		}
	}
}
