using System.Collections;
using UnityEngine;

//ハードヒット演出のためにカメラを揺らすクラス
public class CameraShake : MonoBehaviour
{
	//揺らしたいカメラオブジェクト
	[SerializeField]
	private Camera mainCamera;

	//プレイヤーのアニメーター
	[SerializeField]
	Animator playerAnimator;

	//ハードヒット演出時のアニメーションスピード
	[SerializeField]
	private float hardHitSpeed = 0;

	//すでにシェイクが発生しているかどうか’
	bool isShaking;

	//コルーチンの呼び出し
	public void Shake(float duration, float magnitude)
	{
		if (!isShaking)
			StartCoroutine(DoShake(duration, magnitude));
	}

	//カメラを揺らすコルーチン
	private IEnumerator DoShake(float duration, float magnitude)
	{
		//実行中フラグをオン
		isShaking = true;

		//元のアニメーションスピードをキャッシュ
		var defaultAnimSpeed = playerAnimator.GetFloat("animationSpeed");
		//シェイク発生中だけ速度を落とす
		playerAnimator.SetFloat("animationSpeed", hardHitSpeed);

		//元のカメラ位置をキャッシュ
		var pos = mainCamera.transform.localPosition;

		var elapsedTime = 0f;

		//シェイクの実行
		while (elapsedTime < duration)
		{
			var x = pos.x + Random.Range(-1f, 1f) * magnitude;
			var y = pos.y + Random.Range(-1f, 1f) * magnitude;

			mainCamera.transform.localPosition = new Vector3(x, y, pos.z);

			elapsedTime += Time.deltaTime;

			yield return null;
		}

		//カメラ位置とアニメーションスピードを戻す
		mainCamera.transform.localPosition = pos;
		playerAnimator.SetFloat("animationSpeed", defaultAnimSpeed);

		//シェイク実行中フラグをオフ
		isShaking = false;
	}
}
