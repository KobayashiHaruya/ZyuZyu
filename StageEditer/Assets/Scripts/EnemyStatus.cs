using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Season
{
    Spring,
    Summer,
    Autumn,
    Winter,
}

public enum WaveNum
{
    Wave1 = 0,
    Wave2,
    Wave3,
    Wave4
}

public enum EnemyType
{
    NomalEnemy,
    SwimwearEnemy,
    ShieldEnemy,
    HammerEnemy,
    WorkEnemy,
    CaptainEnemy,
    FastEnemy,
}


public class EnemyStatus : MonoBehaviour {

    [SerializeField, Header("出てくるWave番号")]
    WaveNum m_WaveNum = WaveNum.Wave1;

    [SerializeField, Header("エネミーの種類")]
    EnemyType m_EnemyType = EnemyType.NomalEnemy;

    [SerializeField, Header("キャプテン番号")]
    int m_CaptainNum = 0;

    [SerializeField, Header("Waveが始まってから何秒後に出現するか")]
    float m_SpawnTime = 0.0f;

    public int GetWaveNum()
    {
        return (int)m_WaveNum;
    }

    public int GetEnemyType()
    {
        return (int)m_EnemyType;
    }

    public int GetCaptainNum()
    {
        return m_CaptainNum;
    }

    public float GetSpawnTime()
    {
        return m_SpawnTime;
    }

    public void Update()
    {
        // WaveとSpawnTimeによって出現移動させる
    }
}
