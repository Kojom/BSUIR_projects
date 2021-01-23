using UnityEngine;
using UnityEngine.UI;

public class GameMaster : MonoBehaviour
{
    private static GameMaster instance;
    public Vector2 m_lastCheckPoint;

    private void Awake()
    {
        GameObject.Find("new_player").transform.position = m_lastCheckPoint;
        if(instance == null)
        {
            instance = this;
            DontDestroyOnLoad(instance);
        }
        else
        {
            Destroy(gameObject);
        }
    }

}
