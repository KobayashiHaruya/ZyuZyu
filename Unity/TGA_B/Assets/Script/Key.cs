using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Key : MonoBehaviour
{
    static public int right = 0;
    static public int left = 0;
    static public int up = 0;
    static public int down = 0;


    static public int A = 0;
    static public int B = 0;
    static public int X = 0;
    static public int Y = 0;


    static public int LB = 0;
    static public int RB = 0;

    static public float LT = 0.0f;
    static public float RT = 0.0f;


    static public float leftX = 0.0f;
    static public float leftY = 0.0f;
    static public float rightX = 0.0f;
    static public float rightY = 0.0f;
    static public float padX = 0.0f;
    static public float padY = 0.0f;


    static public float mouseX = 0.0f;
    static public float mouseY = 0.0f;


    static public int mouseLeft = 0;
    static public int mouseRight = 0;

    bool push = true;
    bool rightPush = true;

    void Start()
    {
        Application.targetFrameRate = 60;
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
    }

    void Update()
    {
        leftX = Input.GetAxis("HorizontalLeft");
        leftY = Input.GetAxis("VerticalLeft");
        rightX = Input.GetAxis("HorizontalRight");
        rightY = Input.GetAxis("VerticalRight");

        padX = Input.GetAxisRaw("HorizontalPad");
        padY = Input.GetAxisRaw("VerticalPad");


        LT = -Input.GetAxis("LTrigger");
        RT = -Input.GetAxis("RTrigger");


        mouseX = Input.GetAxis("MouseX");
        mouseY = Input.GetAxis("MouseY");



        if (Input.GetKeyDown(KeyCode.D))
        {
            right = 1;
        }
        else if (Input.GetKey(KeyCode.D))
        {
            right = 2;
        }
        else if (Input.GetKeyUp(KeyCode.D))
        {
            right = 3;
        }
        else
        {
            right = 0;
        }


        if (Input.GetKeyDown(KeyCode.A))
        {
            left = 1;
        }
        else if (Input.GetKey(KeyCode.A))
        {
            left = 2;
        }
        else if (Input.GetKeyUp(KeyCode.A))
        {
            left = 3;
        }
        else
        {
            left = 0;
        }


        if (Input.GetKeyDown(KeyCode.W))
        {
            up = 1;
        }
        else if (Input.GetKey(KeyCode.W))
        {
            up = 2;
        }
        else if (Input.GetKeyUp(KeyCode.W))
        {
            up = 3;
        }
        else
        {
            up = 0;
        }


        if (Input.GetKeyDown(KeyCode.S))
        {
            down = 1;
        }
        else if (Input.GetKey(KeyCode.S))
        {
            down = 2;
        }
        else if (Input.GetKeyUp(KeyCode.S))
        {
            down = 3;
        }
        else
        {
            down = 0;
        }


        if (Input.GetMouseButtonDown(0) || (RT == 1 && push))
        {
            mouseLeft = 1;
            push = false;
        }
        else if (Input.GetMouseButton(0) || RT == 1)
        {
            mouseLeft = 2;
        }
        else if (Input.GetMouseButtonUp(0) || (RT < 1 && !push))
        {
            mouseLeft = 3;
            push = true;
        }
        else
        {
            mouseLeft = 0;
        }

        if (Input.GetMouseButtonDown(1) || (LT == 1 && rightPush))
        {
            mouseRight = 1;
            push = false;
        }
        else if (Input.GetMouseButton(1) || LT == 1)
        {
            mouseRight = 2;
        }
        else if (Input.GetMouseButtonUp(1) || (LT < 1 && !rightPush))
        {
            mouseRight = 3;
            push = true;
        }
        else
        {
            mouseRight = 0;
        }


        if (Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.JoystickButton0))
        {
            A = 1;
        }
        else if (Input.GetKey(KeyCode.Space) || Input.GetKey(KeyCode.JoystickButton0))
        {
            A = 2;
        }
        else if (Input.GetKeyUp(KeyCode.Space) || Input.GetKeyUp(KeyCode.JoystickButton0))
        {
            A = 3;
        }
        else
        {
            A = 0;
        }


        if (Input.GetKeyDown(KeyCode.G) || Input.GetKeyDown(KeyCode.JoystickButton1))
        {
            B = 1;
        }
        else if (Input.GetKey(KeyCode.G) || Input.GetKey(KeyCode.JoystickButton1))
        {
            B = 2;
        }
        else if (Input.GetKeyUp(KeyCode.G) || Input.GetKeyUp(KeyCode.JoystickButton1))
        {
            B = 3;
        }
        else
        {
            B = 0;
        }


        if (Input.GetKeyDown(KeyCode.R) || Input.GetKeyDown(KeyCode.JoystickButton2))
        {
            X = 1;
        }
        else if (Input.GetKey(KeyCode.R) || Input.GetKey(KeyCode.JoystickButton2))
        {
            X = 2;
        }
        else if (Input.GetKeyUp(KeyCode.R) || Input.GetKeyUp(KeyCode.JoystickButton2))
        {
            X = 3;
        }
        else
        {
            X = 0;
        }


        if (Input.GetKeyDown(KeyCode.F) || Input.GetKeyDown(KeyCode.JoystickButton3))
        {
            Y = 1;
        }
        else if (Input.GetKey(KeyCode.F) || Input.GetKey(KeyCode.JoystickButton3))
        {
            Y = 2;
        }
        else if (Input.GetKeyUp(KeyCode.F) || Input.GetKeyUp(KeyCode.JoystickButton3))
        {
            Y = 3;
        }
        else
        {
            Y = 0;
        }


        if (Input.GetKeyDown(KeyCode.Q) || Input.GetKeyDown(KeyCode.JoystickButton4))
        {
            LB = 1;
        }
        else if (Input.GetKey(KeyCode.Q) || Input.GetKey(KeyCode.JoystickButton4))
        {
            LB = 2;
        }
        else if (Input.GetKeyUp(KeyCode.Q) || Input.GetKeyUp(KeyCode.JoystickButton4))
        {
            LB = 3;
        }
        else
        {
            LB = 0;
        }


        if (Input.GetKeyDown(KeyCode.E) || Input.GetKeyDown(KeyCode.JoystickButton5))
        {
            RB = 1;
        }
        else if (Input.GetKey(KeyCode.E) || Input.GetKey(KeyCode.JoystickButton5))
        {
            RB = 2;
        }
        else if (Input.GetKeyUp(KeyCode.E) || Input.GetKeyUp(KeyCode.JoystickButton5))
        {
            RB = 3;
        }
        else
        {
            RB = 0;
        }


    }

}
