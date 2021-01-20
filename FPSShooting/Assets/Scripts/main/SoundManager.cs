using UnityEngine;
using UnityEngine.Audio;

//音量を管理するクラス
public class SoundManager : MonoBehaviour
{
	//メインシーンで使用されているAudioMixer
	[SerializeField]
	AudioMixer mainMixer;

	//BGMのAudioSource
	[SerializeField]
	AudioSource bgmSource;

	//SEのAudioSource
	[SerializeField]
	AudioSource seSource;

	//音量を更新する処理
	public void SetVolume(int bgmVol, int seVol)
	{
		float newBGMVol, newSEVol;

		//BGM音量の設定
		//引数は0～100の値で来るので、-80してMixerのdb範囲と一致させる
		if (bgmVol == 0)
		{
			bgmSource.mute = true;
		}
		else
		{
			bgmSource.mute = false;
			newBGMVol = bgmVol - 80;
			mainMixer.SetFloat("BGM", newBGMVol);
		}

		//SE音量の設定
		//引数は0～100の値で来るので、-80してMixerのdb範囲と一致させる
		if (seVol == 0)
		{
			seSource.mute = true;
		}
		else
		{
			seSource.mute = false;
			newSEVol = seVol - 80;
			mainMixer.SetFloat("SE", newSEVol);
		}
	}
}
