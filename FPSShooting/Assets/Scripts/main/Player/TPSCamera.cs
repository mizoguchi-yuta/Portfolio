using UnityEngine;

//三人称視点のカメラを管理するクラス
public class TPSCamera : MonoBehaviour
{
	//X軸回転を担当するオブジェクト
	[SerializeField]
	private GameObject VerticalRoot;

	//カメラの回転速度に掛ける係数
	float cameraSpeed = 1;

	private void Start()
	{
		SetCameraSpeed(1);
	}

	// Update is called once per frame
	void Update()
	{
		float X_Rotation = Input.GetAxis("Mouse X");
		float Y_Rotation = Input.GetAxis("Mouse Y");

		//X軸回転をカメラに、Y軸回転を垂直回転用オブジェクトに適用
		transform.Rotate(0, X_Rotation * cameraSpeed, 0);
		VerticalRoot.transform.Rotate(-Y_Rotation * cameraSpeed, 0, 0);

		//垂直の角度を一定以上向かないように補正
		if (VerticalRoot.transform.localEulerAngles.x > 60 && VerticalRoot.transform.localEulerAngles.x < 180)
		{
			VerticalRoot.transform.localEulerAngles = new Vector3(60.0f, VerticalRoot.transform.localEulerAngles.y, 0);
		}
		if (VerticalRoot.transform.localEulerAngles.x > 180)
		{
			VerticalRoot.transform.localEulerAngles = new Vector3(0, VerticalRoot.transform.localEulerAngles.y, 0);
		}
	}

	//オプションで設定した値をセット
	public void SetCameraSpeed(int speed)
	{
		cameraSpeed = (float)speed;
	}
}
