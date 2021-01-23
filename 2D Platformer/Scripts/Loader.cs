using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public static class Loader
{

    public static Action onLoaderCallBack;
    private static AsyncOperation async;
    public static float volume = 0.25f;
    public static int gold = 0;
    private class LoadingMonoBehaviour : MonoBehaviour { }

    public static void Load(int scene)
    {
        onLoaderCallBack = () =>
        {
            GameObject loadingGameObject = new GameObject("Loading Game Object");
            loadingGameObject.AddComponent<LoadingMonoBehaviour>().StartCoroutine(LoadSceneAsync(scene));
        };

        SceneManager.LoadScene(1);
    }

    public static IEnumerator LoadSceneAsync(int scene)
    {
        yield return null;

        async = SceneManager.LoadSceneAsync(scene);

        while (!async.isDone)
        {
            yield return null;
        }
    }

    public static float GetProgress()
    {
        if (async != null)
            return async.progress;
        else
        {
            return 1f;
        }
    }

    public static void LoaderCallBack()
    {
        if(onLoaderCallBack != null)
        {
            onLoaderCallBack();
            onLoaderCallBack = null;
        }
    }
}
