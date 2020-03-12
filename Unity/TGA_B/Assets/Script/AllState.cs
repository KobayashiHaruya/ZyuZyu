using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AllState : MonoBehaviour
{
    public Vector2 m_forceHand = new Vector2(3.0f, 3.0f);
    public float m_speedHand = 1.0f;
    public float m_gravityHand = 8.0f;

    public Vector2 m_forceAssult = new Vector2(6.0f, 3.0f);
    public float m_speedAssult = 1.5f;
    public float m_gravityAssult = 5.0f;

    public Vector2 m_forceGrenade = new Vector2(12.0f, 9.0f);
    public float m_speedGrenade = 0.65f;
    public float m_gravityGrenade = 16.0f;

    public Vector2 m_forceShot = new Vector2(3.0f, 3.0f);
    public float m_speedShot = 1.0f;
    public float m_gravityShot= 5.0f;

    public Vector2 m_forceLMG = new Vector2(9.0f, 6.0f);
    public float m_speedLMG = 1.2f;
    public float m_gravityLMG  = 2.0f;

    public Vector2 m_forceSniper = new Vector2(21.0f, 6.0f);
    public float m_speedSniper = 4.0f;
    public float m_gravitySniper = 2.0f;

    public Vector2 m_forceC4 = new Vector2(20.0f, 14.0f);
    public float m_speedC4 = 0.5f;
    public float m_gravityC4 = 5.0f;



    public Vector2 m_forceProx = new Vector2(10.0f, 8.0f);

    public Vector2 m_forceOil = new Vector2(10.0f, 10.0f);


    void Start()
    {
        
    }


    void Update()
    {
        
    }
}
