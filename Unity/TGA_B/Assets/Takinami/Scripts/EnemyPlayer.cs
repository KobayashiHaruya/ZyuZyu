using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyPlayer : MonoBehaviour
{
    [SerializeField]
    private GameObject m_direction;
    [SerializeField]
    private Transform m_instanceTrans;

    //public GameObject g_weaponType;
    //public GameObject g_ammo;

    [SerializeField]
    private GameObject m_bulletHand;
    [SerializeField]
    private GameObject m_bulletAssult;
    [SerializeField]
    private GameObject m_bulletGrenade;
    [SerializeField]
    private GameObject m_bulletShot;
    [SerializeField]
    private GameObject m_bulletLMG;
    [SerializeField]
    private GameObject m_bulletSniper;
    [SerializeField]
    private GameObject m_bulletC4;


    private Quaternion m_bulletRot;

    private int m_weaponF = 0;
    private int m_weaponS = 0;
    private float m_maxTime = 0;
    private float m_time = 0;

    private bool m_reload = false;
    private bool m_reloadType = false;
    private float m_maxReloadTime = 0;
    private float m_reloadTime = 0;

    private bool m_shoot = false;
    private bool m_shot = true;
    private bool m_shootPush = false;
    private bool m_shootType = true;
    private int m_shootAmmo = 1;
    private int m_maxAmmo = 0;
    private int m_ammo = 0;

    private bool m_reloadRequest = false;

    public static int BULLET_NUM = 7;

    private float m_shotTime = 1.0f;
    private float m_timeCount = 0.0f;

    private void Update()
    {
    }

    /*void WeaponType()
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


    }*/

    private void WeaponState()
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

    private void Shoot()
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
        else if (m_reloadRequest && !m_reload)
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
                m_shot = true;
                if (/*Key.mouseLeft == 1 && */m_shot)
                {
                    m_ammo--;
                    m_bulletRot = m_direction.transform.rotation;
                    m_bulletRot.y = transform.rotation.y;
                    m_shootPush = true;
                    m_shot = false;
                    for (int i = 0; i < m_shootAmmo; i++)
                    {
                        BulletShot();
                    }
                }
                //if (Key.mouseLeft == 0)
                //{
                    m_shot = true;
                //}
            }
            if (/*Key.mouseLeft == 2 && */m_shootType && !m_shootPush)
            {
                m_ammo--;
                m_bulletRot = m_direction.transform.rotation;
                m_bulletRot.y = transform.rotation.y;
                m_shootPush = true;
                BulletShot();
            }
        }


    }

    private void BulletShot()
    {

        switch (m_weaponF)
        {
            case 0:
                break;
            case 1:
                Instantiate(m_bulletHand, m_instanceTrans.position, m_bulletRot);
                break;
            case 2:
                Instantiate(m_bulletAssult, m_instanceTrans.position, m_bulletRot);
                break;
            case 3:
                Instantiate(m_bulletGrenade, m_instanceTrans.position, m_bulletRot);
                break;
            case 4:
                Instantiate(m_bulletShot, m_instanceTrans.position, m_bulletRot);
                break;
            case 5:
                Instantiate(m_bulletLMG, m_instanceTrans.position, m_bulletRot);
                break;
            case 6:
                Instantiate(m_bulletSniper, m_instanceTrans.position, m_bulletRot);
                break;
            case 7:
                Instantiate(m_bulletC4, m_instanceTrans.position, m_bulletRot);
                break;
        }
    }

    public void RandomBulletShot()
    {

        if (m_shotTime <= m_timeCount)
        {
            m_weaponF = Random.Range(0, BULLET_NUM);
            WeaponState();
            if (m_shootAmmo == 0) m_reloadRequest = true;
            m_shoot = true;
            Shoot();
            m_timeCount = 0.0f;
        }
        else
            m_timeCount += Time.deltaTime;
    }
}
