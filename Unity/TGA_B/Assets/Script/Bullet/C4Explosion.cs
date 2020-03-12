using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class C4Explosion : MonoBehaviour
{
    float m_time = 0.2f;


    void Start()
    {
        
    }

    void Update()
    {
        m_time -= Time.deltaTime;

        if (m_time <= 0.0f)
        {
            Destroy(gameObject);
        }
    }
}
