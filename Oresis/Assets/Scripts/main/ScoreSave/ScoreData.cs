using System;

//スコアに関するデータを管理するクラス
[Serializable]
public class ScoreData
{
	//スコア,順位は配列の長さまで
	public int[] score = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//ゲームごとの結果スコア
	public int resultScore;

	//順位の入れ替えが発生したかのフラグ
	public bool isSwap;

	//ゲームごとのクリスタル破壊数
	public int breakCount = 0;
}
