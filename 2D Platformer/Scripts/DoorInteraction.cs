using UnityEngine;

namespace Assets.Scripts {
    public class DoorInteraction : MonoBehaviour {
        [SerializeField] private Animator m_animator;
        public bool m_state;
        [SerializeField] int m_nextScene = 0;

        public void HandleDoor() {
            m_animator.SetTrigger("Open");
            m_state = !m_state;
        }

        public void NextLevel()
        {
            Loader.Load(m_nextScene);
        }
    }
}
