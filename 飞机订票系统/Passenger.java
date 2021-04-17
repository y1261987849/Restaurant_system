package com.source;

public class Passenger
{
    public String pas_id;
    public String name;
    public String[] ord_id;
    public int num;

    public Passenger(String id, String name)
    {
        this.pas_id = id;
        this.name = name;
    }
    public Passenger(String id, String name, String[] ord_id, int num)
    {
        this.pas_id = id;
        this.name = name;
        this.num = num;
        for (int i = 0; i < num; i++)
        {
            assert this.ord_id != null;
            this.ord_id[i] = ord_id[i];
        }
    }

    public String toString()
    {
        String str = this.pas_id + " " + this.name + " " + this.num;
        return str;
    }
}
