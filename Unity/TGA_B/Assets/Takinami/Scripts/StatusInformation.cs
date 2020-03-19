using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;

public class StatusInformation : MonoBehaviour
{
    private static StatusInformation mInstance;
    public static StatusInformation Instance
    {
        get
        {
            return mInstance;
        }
    }

    private void Awake()
    {
        if (!Instance) mInstance = this;
    }

    [SerializeField]
    private GameObject m_basePanel = null;
    [SerializeField]
    private Text m_infoText = null;

    private PlayerStatus m_playerStatus = new PlayerStatus();
    private GunStatus m_gunStatus = new GunStatus();

    [SerializeField]
    private bool m_isShow = true;

    private void Update()
    {
        UpdateInfo();
    }

    private void UpdateInfo()
    {
        ShowChange();
        m_infoText.text = "";
        SetPlayerInfo();
        m_infoText.text += "\n";
        SetGunStatus();
    }

    private void ShowChange()
    {
        if (Input.GetKeyDown(KeyCode.Return)) m_isShow = !m_isShow;
        if (m_isShow)
            m_basePanel.SetActive(true);
        else
            m_basePanel.SetActive(false);
    }
    private void SetPlayerInfo()
    {
        m_infoText.text += "<<プレイヤーステータス>>\n";
        var fields = typeof(PlayerStatus).GetFields();
        foreach (var field in fields) m_infoText.text += (field.Name).ToString() + ": " + field.GetValue(m_playerStatus) + "\n";
    }

    private void SetGunStatus()
    {
        m_infoText.text += "<<銃ステータス>>\n";
        var fields = typeof(GunStatus).GetFields();
        foreach (var field in fields) m_infoText.text += (field.Name).ToString() + ": " + field.GetValue(m_gunStatus) + "\n";
    }

    public void SetPlayerStatus(PlayerStatus playerStatus)
    {
        m_playerStatus = playerStatus;
    }

    public void SetGunStatus(GunStatus gunStatus)
    {
        m_gunStatus = gunStatus;
    }
}

public struct PlayerStatus
{
    public string m_playerName;
    public float m_jumpPower;
    public float m_gravity;
    public float m_walkSpeed;
}

public struct GunStatus
{
    public string m_gunName;
    public int m_maxAmmo;
    public int  m_shootAmmo;
    public float  m_maxTime;
    public float m_maxReloadTime;
}
