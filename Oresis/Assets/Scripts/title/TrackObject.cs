using UnityEngine;

//対象を追う動きを管理するクラス
public class TrackObject : MonoBehaviour
{
	//追尾したいゲームオブジェクト
	[SerializeField]
	GameObject trackTarget;

	void Update()
	{
		transform.position = new Vector3(trackTarget.transform.position.x, transform.position.y, trackTarget.transform.position.z - 5);
	}
}
