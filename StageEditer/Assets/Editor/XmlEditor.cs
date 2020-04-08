using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;
using System;
using System.Runtime.Serialization;
using System.Xml;
using System.Xml.Serialization;
using System.Xml.Linq;



// Xmlの親玉
public class GameStage
{
    [XmlElement(ElementName = "Floor")]
    public Floor floor;

    [XmlElement(ElementName = "Barricade")]
    public List<Barricade> barricade;

    [XmlElement(ElementName = "SlowFloor")]
    public List<SlowFloor> slowFloor;

    [XmlElement(ElementName = "Tree")]
    public List<Tree> tree;

    [XmlElement(ElementName = "Enemy")]
    public List<Enemy> enemy;


}

public class Floor
{
    [XmlAttribute(AttributeName = "Type")]
    public string type;

    [XmlAttribute(AttributeName = "Pos")]
    public Vector3 position;

    [XmlAttribute(AttributeName = "Quat")]
    public Quaternion quaternion;

    [XmlAttribute(AttributeName = "Scale")]
    public Vector3 scale;

    [XmlAttribute(AttributeName = "TextureName")]
    public string textureName;
}

public class Barricade
{
    [XmlAttribute(AttributeName = "Type")]
    public string type;

    [XmlAttribute(AttributeName = "Pos")]
    public Vector3 position;

    [XmlAttribute(AttributeName = "Quat")]
    public Quaternion quaternion;

    [XmlAttribute(AttributeName = "Scale")]
    public Vector3 scale;
}

public class SlowFloor
{
    [XmlAttribute(AttributeName = "Type")]
    public string type;

    [XmlAttribute(AttributeName = "Pos")]
    public Vector3 position;

    [XmlAttribute(AttributeName = "Quat")]
    public Quaternion quaternion;

    [XmlAttribute(AttributeName = "Scale")]
    public Vector3 scale;
}

public class Tree
{
    [XmlAttribute(AttributeName = "Type")]
    public string type;

    [XmlAttribute(AttributeName = "Pos")]
    public Vector3 position;

    [XmlAttribute(AttributeName = "Quat")]
    public Quaternion quaternion;

    [XmlAttribute(AttributeName = "Scale")]
    public Vector3 scale;

    [XmlAttribute(AttributeName = "MeshName")]
    public string meshName;
}

public class Enemy
{
    [XmlAttribute(AttributeName = "Type")]
    public string type;

    [XmlAttribute(AttributeName = "Pos")]
    public Vector3 position;

    [XmlAttribute(AttributeName = "Quat")]
    public Quaternion quaternion;

    [XmlAttribute(AttributeName = "Scale")]
    public Vector3 scale;

    [XmlAttribute(AttributeName = "WaveNum")]
    public int waveNum;

    [XmlAttribute(AttributeName = "EnemyType")]
    public int enemyType;

    [XmlAttribute(AttributeName = "CaptainNum")]
    public int captainNum;

    [XmlAttribute(AttributeName = "SpawnTime")]
    public float spawnTime;
}



public class XmlEditor : EditorWindow
{
    string baseName = "stage1";
    string exe = ".xml";

    string fileName = "";

    [MenuItem("Window/XmlEditor")]
    public static void ShowWindow()
    {
        EditorWindow.GetWindow(typeof(XmlEditor));
    }

    private void OnGUI()
    {
        // 入力
        baseName = EditorGUILayout.TextField("ステージ名", baseName);
        exe = EditorGUILayout.TextField("拡張子", exe);
        //GUILayout.Button("Button")
        if (GUILayout.Button("Xmlで書き出す"))
        {
            fileName = baseName + exe;
            if (EditorUtility.DisplayDialog("SaveSelect", fileName + "に保存してもいい？", "ＯＫ！", "ダメ！"))
            {
                CreateXml();
                EditorUtility.DisplayDialog("SaveComplete", Application.dataPath + "/" + fileName + "に保存されました！", "酒井徹君、ありがとう（閉じる）");
            }
        }
    }

    // XMLを保存する
    private void CreateXml()
    {
        GameStage gameStage = new GameStage();

        gameStage.floor = GetFloorData();
        gameStage.barricade = GetBarricadeDatas();
        gameStage.slowFloor = GetSlowFloorDatas();
        gameStage.tree = GetTreeDatas();
        gameStage.enemy = GetEnemyDatas();

        // Asset直下に作成する
        string serializeDataPath = Application.dataPath + "/" + fileName;
        MyXmlSerializer.Serialize(serializeDataPath, gameStage);
    }


    private Floor GetFloorData()
    {
        // PlayerとタグのついたObjectを探す
        GameObject obj = GameObject.FindGameObjectWithTag("Floor");

        var trans = obj.GetComponent<Transform>();
        var floorStatus = obj.GetComponent<FloorStatus>();
        // PlayerのDate作成
        Floor floor = new Floor();
        floor.type = "Floor";
        floor.position = trans.position;
        floor.quaternion = trans.rotation;
        floor.scale = trans.localScale;
        floor.textureName = floorStatus.GetTextureName();
        return floor;
    }

    private List<Barricade> GetBarricadeDatas()
    {
        var objs = GameObject.FindGameObjectsWithTag("Barricade");
        List<Barricade> list = new List<Barricade>();
        foreach (var obj in objs)
        {
            Barricade barricade = new Barricade();
            barricade.type = "Barricade";
            barricade.position = obj.transform.position;
            barricade.quaternion = obj.transform.rotation;
            barricade.scale = obj.transform.localScale;

            list.Add(barricade);
        }

        return list;
    }

    private List<SlowFloor> GetSlowFloorDatas()
    {
        var objs = GameObject.FindGameObjectsWithTag("SlowFloor");
        List<SlowFloor> list = new List<SlowFloor>();
        foreach (var obj in objs)
        {
            SlowFloor slowFloor = new SlowFloor();
            slowFloor.type = "SlowFloor";
            slowFloor.position = obj.transform.position;
            slowFloor.quaternion = obj.transform.rotation;
            slowFloor.scale = obj.transform.localScale;

            list.Add(slowFloor);
        }

        return list;
    }

    private List<Tree> GetTreeDatas()
    {
        var objs = GameObject.FindGameObjectsWithTag("Tree");
        List<Tree> list = new List<Tree>();
        foreach (var obj in objs)
        {
            Tree tree = new Tree();
            var treeStatus = obj.GetComponent<TreeStatus>();
            tree.type = "Tree";
            tree.position = obj.transform.position;
            tree.quaternion = obj.transform.rotation;
            tree.scale = obj.transform.localScale;
            tree.meshName = treeStatus.GetMeshName();
            list.Add(tree);
        }
  
        return list;
    }

    private List<Enemy> GetEnemyDatas()
    {
        var objs = GameObject.FindGameObjectsWithTag("Enemy");
        List<Enemy> list = new List<Enemy>();
        foreach (var obj in objs)
        {
            Enemy enemy = new Enemy();
            var enemyStatus = obj.GetComponent<EnemyStatus>();
            enemy.type = "Enemy";
            enemy.position = obj.transform.position;
            enemy.quaternion = obj.transform.rotation;
            enemy.scale = obj.transform.localScale;
            enemy.waveNum = enemyStatus.GetWaveNum();
            enemy.enemyType = enemyStatus.GetEnemyType();
            enemy.captainNum = enemyStatus.GetCaptainNum();
            enemy.spawnTime = enemyStatus.GetSpawnTime();
            list.Add(enemy);
        }

        return list;
    }
}

public static class MyXmlSerializer
{
    // ファイルに書き出すときに使うシリアライズ
    public static void Serialize<T>(string savePath, T graph)
    {
        using (var sw = new StreamWriter(savePath, false, System.Text.Encoding.UTF8))
        {
            var ns = new XmlSerializerNamespaces();
            ns.Add(string.Empty, string.Empty);

            new XmlSerializer(typeof(T)).Serialize(sw, graph, ns);
        }
    }

    // ファイルを読み取るときに使うデシリアライズ
    public static T Deserialize<T>(string loadPath)
    {
        using (var sr = new StreamReader(loadPath))
        {
            return (T)new XmlSerializer(typeof(T)).Deserialize(sr);
        }
    }
}