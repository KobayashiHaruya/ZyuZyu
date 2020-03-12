using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EbiWeapon : MonoBehaviour
{
    public GameObject m_camera;

    public GameObject g_weaponType;
    public GameObject g_ammo;
    Text t_weapon;
    Text t_ammo;


    public GameObject m_bulletHand;
    public GameObject m_bulletAssult;


    Quaternion m_bulletRot;

    bool m_weaponF = true;
    float m_maxTime = 0;
    float m_time = 0;

    bool m_reload = false;
    bool m_reloadType = false;
    float m_maxReloadTime = 0;
    float m_reloadTime = 0;

    bool m_shoot = false;
    bool m_shot = true;
    bool m_shootPush = false;
    bool m_shootType = true;
    int m_shootAmmo = 1;
    int m_maxAmmo = 0;
    int m_ammo = 0;

    void Start()
    {
        t_weapon = g_weaponType.GetComponent<Text>();
        t_ammo = g_ammo.GetComponent<Text>();
    }

    void Update()
    {

        WeaponType();

        Shoot();

        t_weapon.text = m_weaponF + "";
        t_ammo.text = m_ammo + "";

    }

    void WeaponType()
    {
        if (Key.Y == 1)
        {
            if (m_weaponF)
            {
                m_weaponF = false;
            }
            else
            {
                m_weaponF = true;
            }
            m_shoot = true;
            WeaponState();
        }

    }

    void WeaponState()
    {
        if (m_weaponF)
        {
            m_maxAmmo = 20;
            m_shootAmmo = 1;
            m_maxTime = 0;
            m_maxReloadTime = 50;
            m_shootType = false;
        }
        else
        {
            m_maxAmmo = 30;
            m_shootAmmo = 3;
            m_maxTime = 5;
            m_maxReloadTime = 80;
            m_shootType = true;
        }

        m_ammo = m_maxAmmo;
        m_reloadTime = m_maxReloadTime;
        m_time = 0;


    }

    void Shoot()
    {
        if (m_reload)
        {
            if (m_reloadTime <= 0)
            {
                m_reloadTime = m_maxReloadTime;
                m_ammo = m_maxAmmo;
                m_time = m_maxTime;
                m_reload = false;
                m_shoot = true;
            }
            else
            {
                m_reloadTime--;
            }
        }
        else if (Key.X == 1 && !m_reload)
        {
            m_reload = true;
            m_shoot = false;
            m_shootPush = false;
        }



        if (m_shoot && m_ammo > 0)
        {
            if (m_shootPush)
            {
                m_time--;
                if (m_time <= 0)
                {
                    m_shootPush = false;
                    m_time = m_maxTime;
                }
            }


            if (!m_shootType && !m_shootPush)
            {
                if (Key.mouseLeft == 1 && m_shot)
                {
                    m_ammo--;
                    m_bulletRot = m_camera.transform.rotation;
                    m_bulletRot.y = transform.rotation.y;
                    m_shootPush = true;
                    m_shot = false;
                    for (int i = 0; i < m_shootAmmo; i++)
                    {
                        BulletShot();
                    }
                }
                if (Key.mouseLeft == 0)
                {
                    m_shot = true;
                }
            }
            if (Key.mouseLeft == 2 && m_shootType && !m_shootPush)
            {
                m_ammo--;
                m_bulletRot = m_camera.transform.rotation;
                m_bulletRot.y = transform.rotation.y;
                m_shootPush = true;
                BulletShot();
            }
        }


    }

    void BulletShot()
    {

        if (m_weaponF)
        {
            Instantiate(m_bulletHand, transform.position, m_bulletRot);
        } else
            Instantiate(m_bulletAssult, transform.position, m_bulletRot);
    }
}
