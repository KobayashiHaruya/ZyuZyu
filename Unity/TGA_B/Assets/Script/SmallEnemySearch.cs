using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SmallEnemySearch : MonoBehaviour
{
    Vector3 m_move = Vector3.zero;
    Vector3 m_rot = Vector3.zero;

    public float m_walkSpeed = 0.1f;

    bool m_loc = false;

    Vector3 p1;
    Vector3 p2;

    Vector3 m_dis = Vector3.zero;

    void Start()
    {
        m_move.z = m_walkSpeed;
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
    }

    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.layer == 11)
        {
            if (other.gameObject.tag == "Player")
            {
                m_loc = true;
                p2 = other.gameObject.transform.position;
            }
            else if (other.gameObject.tag == "Enemy")
            {
                m_loc = true;
                p2 = other.gameObject.transform.position;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.gameObject.layer == 11)
        {
            m_loc = false;
        }
    }

}
