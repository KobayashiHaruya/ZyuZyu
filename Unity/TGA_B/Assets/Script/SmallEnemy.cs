using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class SmallEnemy : MonoBehaviour
{
    float m_gravity = 0.1f;

    public AllState g_state;

    public float m_force = 2.0f;

    Vector3 m_hitRot;

    Vector2 m_bulletForce = Vector2.zero;

    Rigidbody r_rigid;


    private void OnCollisionEnter(Collision collision)
    {
        if (transform.tag == "Oil")
        {
            if (collision.gameObject.layer == 11)
            {

            }

            if (collision.gameObject.layer == 9)
            {
                if (collision.gameObject.tag == "Oil")
                {
                    r_rigid.velocity = Vector3.zero;
                    transform.position = new Vector3(0.0f, 5.0f, 0.0f);
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (transform.tag == "Oil")
        {
            if (other.gameObject.layer == 9)
            {
                if (other.gameObject.tag == "Oil")
                {
                    r_rigid.velocity = Vector3.zero;
                    transform.position = new Vector3(0.0f, 5.0f, 0.0f);
                }
            }


            if (other.gameObject.layer == 10)
            {
                m_hitRot = other.transform.eulerAngles;

                if (other.gameObject.tag == "Hand")
                {
                    m_bulletForce = g_state.m_forceHand;
                }
                if (other.gameObject.tag == "Assult")
                {
                    m_bulletForce = g_state.m_forceAssult;
                }
                if (other.gameObject.tag == "Grenade")
                {
                    m_bulletForce = g_state.m_forceGrenade;
                }
                if (other.gameObject.tag == "Shot")
                {
                    m_bulletForce = g_state.m_forceShot;
                }
                if (other.gameObject.tag == "LMG")
                {
                    m_bulletForce = g_state.m_forceLMG;
                }
                if (other.gameObject.tag == "Sniper")
                {
                    m_bulletForce = g_state.m_forceSniper;
                }
                if (other.gameObject.tag == "Prox")
                {
                    m_bulletForce = g_state.m_forceProx;
                }
                if (other.gameObject.tag == "C4")
                {
                    m_bulletForce = g_state.m_forceC4;
                }

                Hit();
            }
        }
    }

    void Start()
    {
        r_rigid = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        r_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {


    }


    void Hit()
    {
        r_rigid.velocity = Vector3.zero;

        float rad = m_hitRot.y * Mathf.Deg2Rad;

        float x = Mathf.Sin(rad);
        float z = Mathf.Cos(rad);

        Vector3 vecForce = (m_bulletForce.x * new Vector3(x, 1.0f, z)) * m_force;

        vecForce.y = m_bulletForce.y * m_force;

        r_rigid.AddForce(vecForce, ForceMode.Impulse);

    }

}
