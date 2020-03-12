using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GrenadeThrow : MonoBehaviour
{
    public GameObject g_smoke;
    public GameObject g_stan;

    Vector3 m_pos = Vector3.zero;

    void Start()
    {
        
    }

    void Update()
    {
        if(Key.LB == 1)
        {
            Throw();
            GameObject smoke = Instantiate(g_smoke, transform.position + m_pos, transform.rotation);
            smoke.transform.parent = transform;
        }

        if(Key.RB == 1)
        {
            Throw();
            GameObject stan = Instantiate(g_stan, transform.position + m_pos, transform.rotation);
            stan.transform.parent = transform;
        }
    }

    void Throw()
    {
        float rad = transform.eulerAngles.y * Mathf.Deg2Rad;

        m_pos.x = Mathf.Sin(rad);
        m_pos.z = Mathf.Cos(rad);

        m_pos = m_pos * 1.0f;

    }

}
