using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonBullet : MonoBehaviour
{
    private Rigidbody m_rigid;

    float m_gravity = 5.0f;
    float m_speed = 0.25f;

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
        m_gravity += 0.05f;
    }

    void Update()
    {

        transform.Translate(0.0f, 0.2f, m_speed);
    }

}
