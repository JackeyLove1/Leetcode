using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    private Rigidbody2D rb;
    private float inputX, inputY;
    private Vector2 movementInput;
    
    public float speed;

    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    private void Update()
    {
        PlayerInput();
    }

    private void PlayerInput()
    {
        inputX = Input.GetAxis("Horizontal");
        inputY = Input.GetAxis("Vertical");
        if (inputX != 0 && inputY != 0) // 允许斜着走
        {
            inputX *= 0.6f;
            inputY *= 0.6f;
        }
        movementInput = new Vector2(inputX, inputY);
    }

    private void FixedUpdate()
    {
        Movement();
    }

    private void Movement()
    {
        rb.MovePosition(rb.position + movementInput * speed * Time.deltaTime);
    }
}