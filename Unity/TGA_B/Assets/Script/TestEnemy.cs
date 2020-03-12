using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestEnemy : MonoBehaviour
{
    public AllState g_state;

    Vector3 m_playerPos = Vector3.zero;

    float m_gravity = 10.0f;

    Vector3 m_hitRot;

    Vector2 m_bulletForce = Vector2.zero;

    Rigidbody r_rigid;


    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.layer == 9)
        {
            if (collision.gameObject.tag == "Oil")
            {
                r_rigid.velocity = Vector3.zero;
                transform.position = Vector3.zero;
            }
        }

        if (collision.gameObject.layer == 11)
        {
            if (collision.gameObject.tag == "Oil")
            {
                m_bulletForce = g_state.m_forceOil;
            }

            Hit();
        }

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == 9)
        {
            if (other.gameObject.tag == "Oil")
            {
                r_rigid.velocity = Vector3.zero;
                transform.position = Vector3.zero;
            }
        }


        if (other.gameObject.layer == 10)
        {
            m_hitRot = other.transform.eulerAngles;
            m_bulletForce = Vector2.zero;

            if (other.gameObject.tag == "Hand")
            {
                m_bulletForce = g_state.m_forceHand;
            }
            if(other.gameObject.tag == "Assult")
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
            if (other.gameObject.tag == "C4")
            {
                m_bulletForce = g_state.m_forceC4;
            }
            if (other.gameObject.tag == "Prox")
            {
                m_bulletForce = g_state.m_forceProx;
            }
            if (other.gameObject.tag == "Oil")
            {
                m_bulletForce = g_state.m_forceOil;
            }

            Hit();
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

        Vector3 force = m_bulletForce.x * new Vector3(x, 0.0f, z);

        force.y = m_bulletForce.y;

        r_rigid.AddForce(force, ForceMode.Impulse);

    }

}
