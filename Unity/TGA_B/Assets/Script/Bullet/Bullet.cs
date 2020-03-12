using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    private Rigidbody r_rigid;

    Vector3 m_speed = new Vector3(0.0f, 0.0f, 0.5f);

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.layer == 9)
        {
            Destroy(gameObject);
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.layer == 9)
        {
            Destroy(gameObject);
        }
    }

    void Start()
    {
    }

    void Update()
    {

        transform.Translate(m_speed);
    }

}
