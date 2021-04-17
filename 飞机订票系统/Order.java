package com.source;

public class Order
{
    public String ord_id;
    public String pas_id;
    public String name;
    public String fli_id;
    public String status;

    public Order(String ord_id, String pas_id, String name, String fli_id, String status)
    {
        this.ord_id = ord_id;
        this.pas_id = pas_id;
        this.name = name;
        this.fli_id = fli_id;
        this.status = status;
    }

    public String toString()
    {
        String str = this.ord_id + " " + this.pas_id + " " + this.name + " " + this.fli_id + " " + status;
        return str;
    }
}
