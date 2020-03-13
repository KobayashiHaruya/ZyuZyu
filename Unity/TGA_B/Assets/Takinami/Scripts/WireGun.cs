using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WireGun : MonoBehaviour
{
    [Header("ワイヤーのプレファブ")]
    [SerializeField]
    private GameObject m_wire = null;
    [Header("ワイヤーの最大到達距離")]
    [SerializeField]
    private float m_maxRange = 100.0f;
    [Header("発射速度")]
    [SerializeField]
    private float m_shotSpeed = 10.0f;
    [Header("巻き取り速度")]
    [SerializeField]
    private float m_rollSpeed = 10.0f;
    [Header("巻き取り解除距離")]
    [SerializeField]
    private float m_unlockDistance = 0.5f;

    [Header("ワイヤーが当たるレイヤー")]
    [SerializeField]
    private LayerMask m_layerMask;

    [Header("レイキャストの生成開始位置")]
    [SerializeField]
    private Transform m_rayStart = null;
    [Header("レイキャストの方向")]
    [SerializeField]
    private Transform m_rayDirection = null;

    [Header("クールタイムの時間")]
    [SerializeField]
    private float m_coolTime = 5.0f;
    [Header("クールタイム情報の表示先")]
    [SerializeField]
    private Text m_coolDownText = null;

    private bool m_isHitting = false;
    private bool m_isLanding = false;
    private LineRenderer m_instanceWire = null;
    private Vector3 m_endPos = Vector3.zero;

    private float m_coolTimeCount = 0.0f;
    private bool m_isCoolDown = false;

    private Rigidbody m_playerRigidbody = null;

    private void Start()
    {
        m_coolTimeCount = m_coolTime;
    }

    private void Update()
    {
        if(CoolTimeCheck()) Shot();
        Roll();
        if (Input.GetKeyDown(KeyCode.Space) || Key.A == 1) ResetWire();
        UpdateWireStartPos();
        UpdateWireEndPos();
    }

    private void Shot()
    {
        m_isCoolDown = false;
        if (Key.LT > 0.0f || Key.mouseRight == 1)
        {
            var res = GetHitGameObject();
            if (res != Vector3.zero && !m_isHitting)
            {
                m_isCoolDown = true;
                m_isHitting = true;
                m_endPos = res;
                CreateWire();
            }
        }
    }

    private void CreateWire()
    {
        var newWire = Instantiate(m_wire, transform.parent);
        var wireComp = newWire.GetComponent<LineRenderer>();
        m_instanceWire = wireComp;
        wireComp.SetPosition(0, transform.position);
        wireComp.SetPosition(1, transform.position);
    }

    private Vector3 GetHitGameObject()
    {
        Vector3 center = m_rayStart.transform.position;
        Ray ray = new Ray(center, m_rayDirection.rotation * Vector3.forward);
        RaycastHit raycastHit;
        Debug.DrawLine(ray.origin, ray.direction * m_maxRange, Color.blue);
        if (Physics.Raycast(ray, out raycastHit, m_maxRange, m_layerMask)) return raycastHit.point;
        return Vector3.zero;
    }

    private void Roll()
    {
        if (!m_instanceWire || !m_isLanding) return;
        transform.position = Vector3.Lerp(transform.position, m_endPos, m_rollSpeed * Time.deltaTime);
        if (Vector3.Distance(transform.position, m_endPos) <= m_unlockDistance) ResetWire();
    }

    private void UpdateWireStartPos()
    {
        if (!m_instanceWire) return;
        m_instanceWire.SetPosition(0, transform.position);
    }

    private void UpdateWireEndPos()
    {
        if (!m_instanceWire) return;
        m_instanceWire.SetPosition(1, Vector3.Lerp(m_instanceWire.GetPosition(1), m_endPos, m_shotSpeed * Time.deltaTime));
        if (Vector3.Distance(m_instanceWire.GetPosition(1), m_endPos) <= m_unlockDistance) m_isLanding = true;
    }

    private void ResetWire()
    {
        if (!m_instanceWire) return;
        Destroy(m_instanceWire.gameObject);
        m_endPos = Vector3.zero;
        m_isHitting = false;
        m_isLanding = false;
    }

    private bool CoolTimeCheck()
    {
        if (m_coolTimeCount > m_coolTime || !m_isCoolDown)
        {
            m_coolTimeCount = 0;
            m_coolDownText.text = "OK";
            return true;
        }
        else
        {
            m_coolDownText.text = ((int)m_coolTime - (int)m_coolTimeCount).ToString();
            m_coolTimeCount += Time.deltaTime;
            return false;
        }
    }
}
