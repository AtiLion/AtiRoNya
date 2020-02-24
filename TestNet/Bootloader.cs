using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using UnityEngine;

public class Bootloader
{
    public static void Main()
    {
        Console.WriteLine("Hello from .NET");
        Console.Title = "Yeeter";

        Debug.Log("Debug.Log test");
        //Debug.Log("Product Name: " + Application.productName);
        //Debug.Log("Unity Version: " + Application.unityVersion);
        //Debug.Log("Target frame rate: " + Application.isEditor);

        /*Debug.Log("Setting target frame rate!");
        Application.targetFrameRate = 69;
        Debug.Log("New target frame rate: " + Application.targetFrameRate);*/
    }
}
