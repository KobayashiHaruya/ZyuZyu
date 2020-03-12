using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Launchar : MonoBehaviour
{
    public Vector3 m_explosionScale = new Vector3(8.0f, 8.0f, 8.0f);

    public AllState g_state;

    float m_time = 0.2f;
    bool m_impact = false;

    Rigidbody r_rigid;

    float m_speed = 0.65f;
    float m_gravity = 16.0f;


    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag != "Player")
        m_impact = true;
    }

    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag != "Player")
            m_impact = true;
    }

    void Start()
    {
        r_rigid = GetComponent<Rigidbody>();

        m_speed = g_state.m_speedGrenade;
        m_gravity = g_state.m_gravityGrenade;
    }

    void FixedUpdate()
    {
        r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {
        if (m_impact)
        {
            m_gravity = 0.0f;
            r_rigid.velocity = Vector3.zero;
            m_speed = 0.0f;

            transform.localScale = m_explosionScale;

            m_time -= Time.deltaTime;

            if (m_time <= 0.0f)
            {
                Destroy(gameObject);
            }
        }
        

        transform.Translate(0.0f, 0.0f, m_speed);

    }
}