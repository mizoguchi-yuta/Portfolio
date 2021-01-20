using UnityEngine;

public class PlayerMove : MonoBehaviour
{
	//プレイヤーの状態
	public enum PlayerState
	{
		Walk,
		Attack,
	}
	PlayerState currentState = PlayerState.Walk;

	public PlayerState GetCurrentState
	{
		get { return currentState; }
		set { currentState = value; }
	}

	//移動速度
	[SerializeField]
	float speed = 6.0F;

	float speedUp = 1;
	public float SetSpeedUp
	{
		set { speedUp = value; }
	}


	[SerializeField]
	private GameObject player;     //キャラクターオブジェクト

	[SerializeField]
	private GameObject mainCamera;       //カメラオブジェクト

	//水平方向の回転を取得するオブジェクト
	[SerializeField]
	private GameObject HorizontalRoot;

	//キャラクターコントローラーを格納する変数
	CharacterController controller;

	//プレイヤーのアニメーターを格納する変数
	Animator playerAnimator;

	//攻撃中かどうかのフラグ
	private bool isAttack;
	public bool IsAttack
	{
		set { isAttack = value; }
	}

	private Vector3 moveDirection = Vector3.zero;  //移動方向
	public Vector3 GetMovceDirection
	{
		get { return moveDirection; }
	}

	private void Start()
	{
		controller = GetComponent<CharacterController>();
		playerAnimator = player.GetComponent<Animator>();
	}

	private void FixedUpdate()
	{
		switch (currentState)
		{
			case PlayerState.Walk:
				MoveCC();
				break;
		}
	}

	//CharacterControllerでの移動
	private void MoveCC()
	{
		//入力値にカメラのオイラー角を掛ける事で、カメラの角度に応じた移動方向に補正する
		moveDirection = Quaternion.Euler(0, HorizontalRoot.transform.localEulerAngles.y, 0) * new Vector3(Input.GetAxis("Horizontal"), moveDirection.y, Input.GetAxis("Vertical"));

		//移動方向をローカルからワールド空間に変換する
		moveDirection = transform.TransformDirection(moveDirection);

		//移動速度を掛ける
		moveDirection *= speed * speedUp;

		//移動方向に向けてキャラを回転させる
		if (moveDirection.x != 0 || moveDirection.z != 0)
			player.transform.rotation = Quaternion.LookRotation(new Vector3(moveDirection.x, 0, moveDirection.z));

		//y軸方向への移動に重力を加える
		moveDirection.y += Physics.gravity.y * Time.fixedDeltaTime;

		//地面についていたら重力を0にする
		if (controller.isGrounded)
			moveDirection.y = 0;

		//CharacterControllerを移動させる
		controller.Move(moveDirection * Time.deltaTime);
	}
}
