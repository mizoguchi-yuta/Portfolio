using System.Collections;
using UnityEngine;
using UnityEngine.UI;

//スコアのUIを管理するクラス
public class ScoreManager : MonoBehaviour
{
	//右上に表示するスコア
	[SerializeField]
	private Text scoreText;

	//スコア
	private int score;
	public int Score
	{
		get { return score; }
	}

	//スコアを表示するキャンバスのルート
	private Canvas canvasRoot;
	public Canvas CanvasRoot
	{
		set { canvasRoot = value; }
	}

	//クリスタルの上に表示するスコアのプレハブ
	[SerializeField]
	GameObject scorePrefab;

	private void Start()
	{
		scoreText.text = "0";
	}

	//右上のスコアの更新
	public void UpdateScore(int addNum, Vector3 pos)
	{
		//加算するスコア
		int value = addNum;

		//破壊したクリスタルの座標
		Vector3 crystalPos = pos;

		float oldScore = score;
		float newScore = score + value;
		score = (int)newScore;

		StartCoroutine(AddScore(oldScore, newScore));
		CreateScoreValue(value, crystalPos);
	}

	//クリスタルを破壊した位置にスコアのUIを生成
	void CreateScoreValue(int value, Vector3 pos)
	{
		var score = Instantiate(scorePrefab, canvasRoot.transform);
		score.GetComponentInChildren<Text>().text = "+" + value;
		score.GetComponent<RectTransform>().position = RectTransformUtility.WorldToScreenPoint(Camera.main, new Vector3(pos.x, pos.y + 3, pos.z));
	}

	//リールアニメーションでスコアを加算していくコルーチン
	IEnumerator AddScore(float oldScore, float newScore)
	{
		//加算前のスコアから加算後のスコアまでインクリメントを繰り返し、アニメーションさせる
		for (int i = (int)oldScore; i < (int)newScore; i++)
		{
			oldScore++;
			yield return new WaitForSeconds(0.01f);
			scoreText.text = oldScore.ToString();
		}

		yield break;
	}
}
