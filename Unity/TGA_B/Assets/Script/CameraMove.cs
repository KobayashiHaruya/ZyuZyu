using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    Transform m_playerRot;

    float maxAngle = 0.4f;
    float minAngle = -0.4f;

    float m_aim = 2.5f;

    void Start()
    {
        m_playerRot = transform.parent;
    }

    void Update()
    {

        float m_RotMX = Key.mouseX;
        float m_RotMY = Key.mouseY;

        float m_RotCX = Key.rightX;
        float m_RotCY = Key.rightY;

        float m_RotX = m_RotMX + m_RotCX;
        float m_RotY = m_RotMY + m_RotCY;

        m_playerRot.transform.Rotate(0, m_RotX * m_aim, 0);

        float nowAngle = transform.localRotation.x;

        if (0 < m_RotY)
        {
            if (minAngle <= nowAngle)
            {
                transform.Rotate(-m_RotY * m_aim, 0, 0);
            }
        }
        else
        {
            if (nowAngle <= maxAngle)
            {
                transform.Rotate(-m_RotY * m_aim, 0, 0);
            }
        }
    }
}
