using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RandomNumber : MonoBehaviour
{
    [SerializeField]
    private Text m_number = null;
    [SerializeField]
    private int m_min = 0;
    [SerializeField]
    private int m_max = 0;

    [SerializeField]
    [Space(15)]
    private Image m_slider = null;

    [SerializeField]
    [Space(15)]
    private bool m_startRandom = false;

    private int m_now = 0;
    private bool m_isUp = true;

    private void Start()
    {
        if (m_startRandom) m_now = Random.Range(m_min, m_max);
    }

    private void Update()
    {
        CreateNumber();
        m_number.text = m_now.ToString();
        UpdateSlider();
    }

    private void CreateNumber()
    {
        if (m_now < m_max && m_isUp)
            m_now++;
        else if (m_now > m_min && !m_isUp)
            m_now--;
        else if (m_now == m_min)
            m_isUp = true;
        else
            m_isUp = false;
    }

    private void UpdateSlider()
    {
        if (!m_slider) return;
        m_slider.fillAmount = m_now / m_slider.rectTransform.rect.width;
    }
}
