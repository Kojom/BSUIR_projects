using UnityEngine;

namespace Assets.Scripts {
    public class CamMove : MonoBehaviour {
        [SerializeField]
        private GameObject m_player;

        private void Start()
        {
            GetComponent<AudioSource>().volume = Loader.volume;
            if(Loader.volume == 0)
            {
                GetComponent<AudioSource>().mute = true;
            }
        }

        // Update is called once per frame
        private void Update() {
            if(m_player) transform.position = new Vector3(m_player.transform.position.x, m_player.transform.position.y, -10);
        }
    }
}
