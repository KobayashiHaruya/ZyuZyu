using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloorStatus : MonoBehaviour {

    [SerializeField, Header("床のテクスチャ情報")]
    Season m_TextureName = Season.Spring;

    public string GetTextureName()
    {
        return ("Floor" + m_TextureName.ToString() + ".png");
    }

}
