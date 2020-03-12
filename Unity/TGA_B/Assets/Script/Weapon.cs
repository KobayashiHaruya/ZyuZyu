using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Weapon : MonoBehaviour
{
    public GameObject m_camera;

    public GameObject g_weaponType;
    public GameObject g_ammo;
    Text t_weapon;
    Text t_ammo;


    public GameObject m_bulletHand;
    public GameObject m_bulletAssult;
    public GameObject m_bulletGrenade;
    public GameObject m_bulletShot;
    public GameObject m_bulletLMG;
    public GameObject m_bulletSniper;
    public GameObject m_bulletC4;


    Quaternion m_bulletRot;

    int m_weaponF = 0;
    int m_weaponS = 0;
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

        t_weapon.text = m_weaponF + "   " + m_weaponS;
        t_ammo.text = m_ammo + "";

    }

    void WeaponType()
    {
        if (Key.Y == 1)
        {
            if (m_weaponF >= 7)
            {
                m_weaponF = 0;
                m_shoot = false;
            }
            else
            {
                m_weaponF++;
                m_shoot = true;
            }
            WeaponState();
        }

        if (Input.GetKeyDown(KeyCode.G))
        {
            if (m_weaponS >= 7)
            {
                m_weaponS = 0;
                m_shoot = false;
            }
            else
            {
                m_weaponS++;
                m_shoot = true;
            }
            WeaponState();
        }


    }

    void WeaponState()
    {
        switch (m_weaponF)
        {
            case 0:
                m_maxAmmo = 0;
                m_shootAmmo = 0;
                m_maxTime = 0;
                m_maxReloadTime = 50;
                m_shootType = false;
                break;
            case 1:
                m_maxAmmo = 20;
                m_shootAmmo = 1;
                m_maxTime = 0;
                m_maxReloadTime = 50;
                m_shootType = false;
                break;
            case 2:
                m_maxAmmo = 30;
                m_shootAmmo = 3;
                m_maxTime = 5;
                m_maxReloadTime = 80;
                m_shootType = true;
                break;
            case 3:
                m_maxAmmo = 6;
                m_shootAmmo = 1;
                m_maxTime = 0;
                m_maxReloadTime = 360;
                m_shootType = false;
                break;
            case 4:
                m_maxAmmo = 2;
                m_shootAmmo = 12;
                m_maxTime = 0;
                m_maxReloadTime = 90;
                m_shootType = false;
                break;
            case 5:
                m_maxAmmo = 100;
                m_shootAmmo = 1;
                m_maxTime = 12;
                m_maxReloadTime = 240;
                m_shootType = true;
                break;
            case 6:
                m_maxAmmo = 6;
                m_shootAmmo = 1;
                m_maxTime = 80;
                m_maxReloadTime = 100;
                m_shootType = false;
                break;
            case 7:
                m_maxAmmo = 999;
                m_shootAmmo = 1;
                m_maxTime = 0;
                m_maxReloadTime = 0;
                m_shootType = false;
                break;
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

        switch (m_weaponF)
        {
            case 0:
                break;
            case 1:
                Instantiate(m_bulletHand, transform.position, m_bulletRot);
                break;
            case 2:
                Instantiate(m_bulletAssult, transform.position, m_bulletRot);
                break;
            case 3:
                Instantiate(m_bulletGrenade, transform.position, m_bulletRot);
                break;
            case 4:
                Instantiate(m_bulletShot, transform.position, m_bulletRot);
                break;
            case 5:
                Instantiate(m_bulletLMG, transform.position, m_bulletRot);
                break;
            case 6:
                Instantiate(m_bulletSniper, transform.position, m_bulletRot);
                break;
            case 7:
                Instantiate(m_bulletC4, transform.position, m_bulletRot);
                break;
        }
    }

}
