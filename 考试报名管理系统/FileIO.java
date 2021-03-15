package com.source;

import javax.swing.*;
import java.io.*;
import java.util.Vector;

public class FileIO
{
    public static Vector Read(String filepath) throws Exception
    {
        Vector v = new Vector(2000);
        File f = new File(filepath);
        InputStream ins = new FileInputStream(f);
        InputStreamReader insr =  new InputStreamReader(ins, "utf-8");
        BufferedReader br = new BufferedReader(insr);

        String str = "";
        while ((str = br.readLine()) != null)
        {
            v.add(str);
        }

        br.close();
        insr.close();
        ins.close();
        return v;
    }

    public static void Write(String filepath, Vector<String> Content) throws IOException
    {
        File f = new File(filepath);
        f.delete();
        f = new File(filepath);
        FileOutputStream fouts = null;
        OutputStreamWriter outsw = null;

        f.createNewFile();
        fouts = new FileOutputStream(f, true);
        outsw = new OutputStreamWriter(fouts, "utf-8");
        for (int i = 0; i < Content.size(); i++)
        {
            outsw.write(Content.get(i));
            outsw.write("\n");
        }

        outsw.close();
        fouts.close();

    }
}
