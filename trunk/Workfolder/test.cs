//==============================================================================
//
// Project: xMono
// Author(s): adamix
// License: See LICENSE in root directory
//
//==============================================================================

using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

class MonoEmbed
{
	[MethodImplAttribute(MethodImplOptions.InternalCall)]
	extern public static void Func(int num, string text, float x);

    [MethodImplAttribute(MethodImplOptions.InternalCall)]
    extern public static string Func2(string text);

    [DllImport("__Internal", EntryPoint = "PrintSomething")]
    static public extern void PrintSomething(string str);
}

class Module
{
    public delegate void delegtest(int[] i);
    public event delegtest delegevent;

    void Eventeg(int[] i)
    {
        Console.WriteLine("Delegate: " + i[0]);
    }

    static void RunStatic()
    {
        MonoEmbed.Func(6, "testing", 0.15f);
        Console.WriteLine("Func2: " + MonoEmbed.Func2("blabla"));
    }
	void Run()
	{
	    MonoEmbed.Func(5, "testing", 0.15f);
	}
    public int Test(string text, int num, float x)
    {
        MonoEmbed.Func(num, text, x);
        Console.WriteLine("Got: " + text + "   " + num);
        return 1337;
    }
    public void Test2()
    {
        MonoEmbed.Func(1337, "lolwat", 0.1f);
    }
    public void VectorTest(CVector3 vec)
    {
        MonoEmbed.PrintSomething(vec.x + " " + vec.y + " " + vec.z);
    }
    public int Testing(int i)
    {
        return 11111 + i;
    }
    public string stringTest(string str)
    {
	    return str + "added";
    }
    public CVector3 end1()
    {
        delegevent += Eventeg;
        return new CVector3(5, 6, 57);
    }
    public string end2(CVector3 vec)
    {
        Console.WriteLine("Vector: " + vec.x + " " + vec.y + " " + vec.z);
        return "Vec:" + vec.x + " " + vec.y + " " + vec.z;
    }
    public void arraysInt(int[] i)
    {
        Console.WriteLine("Ints: " + i.Length);
        for (int z = 0; z < i.Length; z++)
        {
            Console.WriteLine("Ints: " + i[z].ToString());
        }
    }
    public void arraysString(string[] i)
    {
        Console.WriteLine("Strings: " + i.Length);
        for (int z = 0; z < i.Length; z++)
        {
            Console.WriteLine("Strings: " + i[z]);
        }
    }
    public void arraysFloat(float[] i)
    {
        Console.WriteLine("Floats: " + i.Length);
        for (int z = 0; z < i.Length; z++)
        {
            Console.WriteLine("Floats: " + i[z].ToString());
        }
    }
    public void arraysVector(CVector3[] i)
    {
        Console.WriteLine("Vectors: " + i.Length);
        for (int z = 0; z < i.Length; z++)
        {
            Console.WriteLine("Vectors: " + i[z].x + " " + i[z].y + " " + i[z].z);
        }
    }
}

class Test
{
    static void Testing(Module module)
    {
        module.Test2();
    }
}