﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stan : MonoBehaviour
{
    float m_desTime = 15.0f;

    void Start()
    {

    }

    void Update()
    {
        m_desTime -= Time.deltaTime;

        if (m_desTime <= 0.0f)
        {
            Destroy(gameObject);
        }

    }
}