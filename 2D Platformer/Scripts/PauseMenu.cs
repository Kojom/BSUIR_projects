using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PauseMenu : MonoBehaviour
{
    public GameObject pauseMenu;
    public Slider slider;

    private void Start()
    {
        slider.normalizedValue = Loader.volume;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            pauseMenu.active = !pauseMenu.active;
            if (pauseMenu.active)
            {
                Time.timeScale = 0f;
            }
            else
            {
                Time.timeScale = 1f;
            }
        }

    }

    public void Resume()
    {
        Time.timeScale = 1f;
        pauseMenu.active = false;
    }

    public void MainMenu()
    {
        Loader.Load(0);
    }

    public void UpdateVolume()
    {
        Loader.volume = slider.normalizedValue;
        if (Loader.volume == 0)
        {
            GameObject.Find("Main Camera").GetComponent<Camera>().GetComponent<AudioSource>().mute = true;
        }
        else
        {
            GameObject.Find("Main Camera").GetComponent<Camera>().GetComponent<AudioSource>().mute = false;
            GameObject.Find("Main Camera").GetComponent<Camera>().GetComponent<AudioSource>().volume = Loader.volume;
        }
    }
}
