using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Assult : MonoBehaviour
{
    Rigidbody r_rigid;

    public AllState g_state;

    float m_speed = 1.5f;
    float m_gravity = 5.0f;

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == 9)
        {
            Destroy(gameObject);
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.layer == 9)
        {
            Destroy(gameObject);
        }
    }

    void Start()
    {
        r_rigid = GetComponent<Rigidbody>();
        m_speed = g_state.m_speedAssult;
        m_gravity = g_state.m_gravityAssult;
    }

    void FixedUpdate()
    {
        r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {
        transform.Translate(0.0f, 0.0f, m_speed);
    }
}
