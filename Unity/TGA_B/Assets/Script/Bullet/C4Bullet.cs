using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class C4Bullet : MonoBehaviour
{

    public GameObject g_explosion;

    public AllState g_state;

    bool m_impact = false;
    bool m_objHit = false;
    bool m_push = false;

    Rigidbody r_rigid;

    float m_speed = 0.5f;
    float m_gravity = 5.0f;


    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag != "Player")
        {
            transform.parent = other.transform;
            m_objHit = true;
        }

        if (other.gameObject.layer == 10)
        {
            if (other.gameObject.tag != "C4Body")
            {
                m_push = true;
            }
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag != "Player")
        {
            transform.parent = collision.transform;
            m_objHit = true;
        }

        if (collision.gameObject.layer == 10)
        {
            if (collision.gameObject.tag != "C4Body")
            {
                m_push = true;
            }
        }
    }

    void Start()
    {
        r_rigid = GetComponent<Rigidbody>();

        m_speed = g_state.m_speedC4;
        m_gravity = g_state.m_gravityC4;
    }

    void FixedUpdate()
    {
        if (!m_objHit)
        {
            r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
        }
    }

    void Update()
    {
        if (m_objHit)
        {
            r_rigid.velocity = Vector3.zero;
        }
        else
        {
            transform.Translate(0.0f, 0.0f, m_speed);
        }

        if (Key.mouseLeft == 1)
        {
            m_push = true;
        }

        if (m_push)
        {
            transform.parent = null;
            Instantiate(g_explosion, transform.position, transform.rotation);
            Destroy(gameObject);
        }

    }

}