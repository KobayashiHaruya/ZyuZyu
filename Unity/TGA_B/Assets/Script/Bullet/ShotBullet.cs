using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShotBullet : MonoBehaviour
{
    Rigidbody r_rigid;

    public AllState g_state;

    Vector3 m_speed = Vector3.forward;
    float m_gravity = 8.0f;

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

        m_speed.x = Random.Range(-0.1f, 0.1f);
        m_speed.y = Random.Range(-0.1f, 0.1f);

        m_speed.z = g_state.m_speedHand;
        m_gravity = g_state.m_gravityHand;

    }

    void FixedUpdate()
    {
        r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {

        transform.Translate(m_speed);

    }
}
