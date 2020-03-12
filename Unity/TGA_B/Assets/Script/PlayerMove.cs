using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    public GameObject g_smoke;

    Vector3 m_move = new Vector3(0.0f, 0.0f, 0.0f);
    bool m_jump = false;
    float m_defaultJump = 6.5f;
    float m_jumpPower = 6.5f;
    float m_gravity = 0.1f;

    float m_defaultSpeed = 0.08f;
    float m_walkSpeed = 0.15f;
    float m_dashSpeed = 0.25f;

    Rigidbody r_rigid;

    public Vector2 m_enemyBullet = new Vector2(5.0f, 5.0f);

    Vector3 m_hitRot;

    Vector2 m_bulletForce = Vector2.zero;



    void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.layer == 9)
        {
            m_move.y = 0.0f;
            m_jump = true;
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
                m_hitRot = collision.transform.eulerAngles;

                m_bulletForce = m_enemyBullet;
                Hit();
            }
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
            if (other.gameObject.tag == "Enemy")
            {
                m_hitRot = other.transform.eulerAngles;

                m_bulletForce = m_enemyBullet;
                Hit();
            }
        }

        if (other.gameObject.layer == 13)
        {
            if(other.gameObject.tag == "Smoke")
            {
                g_smoke.SetActive(true);
            }
            if(other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed / 2.0f;
                m_jumpPower = m_defaultJump / 2.0f;
            }
        }

    }

    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.layer == 13)
        {
            if (other.gameObject.tag == "Smoke")
            {
                g_smoke.SetActive(true);
            }
            if (other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed / 2.0f;
                m_jumpPower = m_defaultJump / 2.0f;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.layer == 13)
        {
            if (other.gameObject.tag == "Smoke")
            {
                g_smoke.SetActive(false);
            }
            if (other.gameObject.tag == "Stan")
            {
                m_walkSpeed = m_defaultSpeed;
                m_jumpPower = m_defaultJump;
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
        Move();

        transform.Translate(m_move);
    }

    void Move()
    {
        if (Key.right != 0)
        {
            m_move.x = m_walkSpeed;
        }
        else if (Key.left != 0)
        {
            m_move.x = -m_walkSpeed;
        }
        else if(Key.leftX != 0)
        {
            m_move.x = m_walkSpeed * Key.leftX;
        }
        else
        {
            m_move.x = 0.0f;
        }

        if (Key.up != 0)
        {
            if (Key.B == 2)
            {
                m_move.z = m_dashSpeed;
            }
            else
            {
                m_move.z = m_walkSpeed;
            }
        }
        else if (Key.down != 0)
        {
            m_move.z = -m_walkSpeed;
        }
        else if (Key.leftY != 0)
        {
            if (Key.B == 2 && Key.leftY > 0)
            {
                m_move.z = m_dashSpeed;
            }
            else
            {
                m_move.z = m_walkSpeed * Key.leftY;
            }
        }
        else
        {
            m_move.z = 0.0f;
        }


        if (Key.A == 1 && m_jump)
        {
            r_rigid.velocity = new Vector3(r_rigid.velocity.x, m_jumpPower, r_rigid.velocity.z);
            m_jump = false;
        }

    }


    void Hit()
    {
        r_rigid.velocity = Vector3.zero;

        float rad = m_hitRot.y * Mathf.Deg2Rad;

        float x = Mathf.Sin(rad);
        float z = Mathf.Cos(rad);

        Vector3 force = m_bulletForce.x * new Vector3(x, 1.0f, z);

        r_rigid.AddForce(force, ForceMode.Impulse);

    }


}
