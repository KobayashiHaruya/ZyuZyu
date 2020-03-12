using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySearch : MonoBehaviour
{
    Vector3 m_move = Vector3.zero;
    Vector3 m_rot = Vector3.zero;
    bool m_jump = false;
    float m_defaultJump = 6.5f;
    float m_jumpPower = 6.5f;

    float m_defaultSpeed = 0.08f;
    public float m_walkSpeed = 0.08f;

    bool m_loc = false;

    Vector3 p1;
    Vector3 p2;

    Vector3 m_dis = Vector3.zero;

    void Start()
    {
    }


    void Update()
    {
        if (m_loc)
        {
            GetAim();
        }
    }


    void GetAim()
    {
        m_rot = transform.eulerAngles;
        p1 = transform.position;
        Vector3 dis = p2 - p1;
        m_rot.y = (Mathf.Atan2(dis.x, dis.z) * Mathf.Rad2Deg) + 360.0f;
        transform.eulerAngles = m_rot;
        m_move.z = m_walkSpeed;
        transform.Translate(m_move);


    }

    void BulletHit(Vector3 rot)
    {
        Vector3 hitRot = transform.eulerAngles;
        hitRot.y = rot.y + 180.0f;
        transform.eulerAngles = hitRot;
    }


    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == 10)
        {
            if (!m_loc)
            {
                BulletHit(other.gameObject.transform.eulerAngles);
            }
        }

        if (other.gameObject.layer == 13)
        {
            if (other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed / 2.0f;
                m_jumpPower = m_defaultJump / 2.0f;
            }
        }

    }


    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.layer == 11)
        {
            m_loc = true;
            if (other.gameObject.tag == "Player")
            {
                p2 = other.gameObject.transform.position;
            }
            else if (other.gameObject.tag == "Oil")
            {
                p2 = other.gameObject.transform.position;
            }
            else if (other.gameObject.tag == "Enemy")
            {
                p2 = other.gameObject.transform.position;
            }
        }


        if (other.gameObject.layer == 13)
        {
            if (other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed / 2.0f;
                m_jumpPower = m_defaultJump / 2.0f;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.layer == 11)
        {
            m_loc = false;
        }

        if (other.gameObject.layer == 13)
        {
            if (other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed;
                m_jumpPower = m_defaultJump;
            }
        }
    }

}
