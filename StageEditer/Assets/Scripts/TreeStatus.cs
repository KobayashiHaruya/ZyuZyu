using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class TreeStatus : MonoBehaviour {

    [SerializeField, Header("木のメッシュ情報")]
    Season m_MeshName = Season.Spring;

    public string GetMeshName()
    {
        return ("Tree" + m_MeshName.ToString() + ".bmf");
    }


}
