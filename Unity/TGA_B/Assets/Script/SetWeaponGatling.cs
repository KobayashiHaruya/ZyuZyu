using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetWeaponGatling : MonoBehaviour
{
    public GameObject m_bullet;
    public GameObject m_player;

    bool m_shoot = false;

    bool m_enter = false;

    int m_maxTime = 2;
    int m_time = 0;


    void OnTriggerStay(Collider other)
    {
        if (other.gameObject.tag == "Player" || other.gameObject.tag == "Enemy")
        {
            m_enter = true;
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player" || other.gameObject.tag == "Enemy")
        {
            m_enter = false;
        }
    }

    void Start()
    {
        m_time = m_maxTime;
    }

    void Update()
    {
        if (m_shoot)
        {
            m_time--;
            if (m_time <= 0)
            {
                m_shoot = false;
                m_time = m_maxTime;
            }
        }

        if (m_enter)
        {
            if (Key.mouseLeft == 2 && !m_shoot)
            {
                Instantiate(m_bullet, transform.position, m_player.transform.rotation);
                m_shoot = true;
            }
        }
    }
}
