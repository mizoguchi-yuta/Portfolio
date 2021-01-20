using UnityEngine;

//割り当てられたオブジェクトを一定時間で削除するためのクラス
public class SelfDestroy : MonoBehaviour
{
	[SerializeField]
	float LifeTime = 5.0f;

	private float elapsedTime;

	void Update()
	{
		elapsedTime += Time.deltaTime;
		if (elapsedTime >= LifeTime)
		{
			Destroy(this.gameObject);
		}
	}
}
