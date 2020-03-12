using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Proximity : MonoBehaviour
{
    public GameObject g_prox;

    Vector3 m_rot = Vector3.zero;

    int m_maxTime = 5;
    int m_time = 5;

    bool m_attack = false;



    void Start()
    {
        m_time = m_maxTime;
    }

    void Update()
    {
        if (m_attack)
        {
            m_time--;
        }

        m_rot = transform.eulerAngles;

        if (Key.B == 1 && !m_attack)
        {
            g_prox.SetActive(true);
            g_prox.transform.eulerAngles = m_rot;
            m_attack = true;
        }


        if (m_time <= 0)
        {
            m_attack = false;
            m_time = m_maxTime;
            g_prox.SetActive(false);
        }

    }
}
