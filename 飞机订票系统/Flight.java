package com.source;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Flight
{
    public String fli_id;
    public LocalDateTime takeoff_time;
    public LocalDateTime arrival_time;
    public String takeoff_city;
    public String arrival_city;
    public double price;
    public double dis;
    public int t_num;

    public Flight(String id, LocalDateTime takeoff_time, LocalDateTime arrival_time, String takeoff_city, String arrival_city, double price, double dis, int t_num)
    {
        this.fli_id = id;
        this.takeoff_time = takeoff_time;
        this.arrival_time = arrival_time;
        this.takeoff_city = takeoff_city;
        this.arrival_city = arrival_city;
        this.price = price;
        this.dis = dis;
        this.t_num = t_num;
    }

    public String toString()
    {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy/MM/dd-HH:mm");
        String str = this.fli_id + " " +  dtf.format(this.takeoff_time) + " " + dtf.format(this.arrival_time) + " " + this.takeoff_city + " " + this.arrival_city + " " + this.price + " " + this.dis + " " + this.t_num;
        return str;
    }
}
