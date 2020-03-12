using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GatlingBullet : MonoBehaviour
{
    private Rigidbody m_rigid;

    float m_gravity = 2.0f;
    float m_speed = 1.2f;

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
        m_rigid = GetComponent<Rigidbody>();
    }

    void FixedUpdate()
    {
        m_rigid.AddForce(new Vector3(0.0f, -m_gravity, 0.0f), ForceMode.Acceleration);
    }

    void Update()
    {

        transform.Translate(0.0f, 0.0f, m_speed);
    }

}