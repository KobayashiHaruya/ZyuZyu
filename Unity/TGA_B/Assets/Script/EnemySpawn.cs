using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemySpawn : MonoBehaviour
{
    public GameObject g_Enemy;
    public GameObject g_smallEnemy;


    void Start()
    {
        
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Z))
        {
            Instantiate(g_Enemy, transform.position, Quaternion.identity);
        }

        if (Input.GetKeyDown(KeyCode.X))
        {
            Instantiate(g_smallEnemy, transform.position, Quaternion.identity);
        }



    }
}
