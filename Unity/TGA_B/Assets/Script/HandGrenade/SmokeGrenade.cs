using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SmokeGrenade : MonoBehaviour
{
    public GameObject g_smoke;

    float m_impactTime = 2.0f;

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
        if(collision.gameObject.layer == 10)
        {
            if(collision.gameObject.tag != "C4Body")
            {
                m_impact = true;
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == 10)
        {
            if (other.gameObject.tag != "C4Body")
            {
                m_impact = true;
            }
        }
    }

    void FixedUpdate()
    {
        if(!m_throw)
        r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {
        if(Key.LB == 3 && m_throw)
        {
            r_rigid.useGravity = true;
            transform.parent = null;
            Throw();
            m_throw = false;
        }


        m_impactTime -= Time.deltaTime;


        if(m_impactTime <= 0.0f)
        {
            Instantiate(g_smoke, transform.position, Quaternion.identity);
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
