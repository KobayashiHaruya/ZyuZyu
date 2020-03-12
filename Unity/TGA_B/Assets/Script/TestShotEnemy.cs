using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestShotEnemy : MonoBehaviour
{
    public GameObject g_bullet;

    public bool fire = true;
    public int m_maxTime = 120;
    int m_time = 120;

    void Start()
    {
        m_time = m_maxTime;
    }

    void Update()
    {
        if (fire)
        {
            m_time--;
            if (m_time <= 0)
            {
                Instantiate(g_bullet, transform.position, transform.rotation);
                m_time = m_maxTime;
            }
        }
    }
}
