using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StanGrenade : MonoBehaviour
{
    public GameObject g_stan;

    bool m_throw = true;
    bool m_impact = false;

    Rigidbody r_rigid;

    float m_gravity = 1.0f;
    float m_speed = 20.0f;


    void Start()
    {
        r_rigid = GetComponent<Rigidbody>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.layer != 13)
        {
            if (collision.gameObject.layer != 12)
            {
                m_impact = true;
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer != 13)
        {
            if (other.gameObject.layer != 12)
            {
                m_impact = true;
            }
        }
    }

    void FixedUpdate()
    {
        if (!m_throw)
            r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {
        if (Key.RB == 3 && m_throw)
        {
            r_rigid.useGravity = true;
            transform.parent = null;
            Throw();
            m_throw = false;
        }

        if (m_impact && !m_throw)
        {
            Instantiate(g_stan, transform.position, Quaternion.identity);
            Destroy(gameObject);
        }
    }


    void Throw()
    {
        r_rigid.velocity = Vector3.zero;

        float rad = transform.eulerAngles.y * Mathf.Deg2Rad;


        float x = Mathf.Sin(rad);
        float z = Mathf.Cos(rad);

        Vector3 force = m_speed * new Vector3(x, 0.0f, z);

        force.y = 5.0f;

        r_rigid.AddForce(force, ForceMode.Impulse);

    }

}