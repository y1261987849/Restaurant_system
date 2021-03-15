package com.source;

public class Stu
{
    public String id;
    public String name;
    public String gender;
    public float score;
    public int age;

    public Stu(String id, String name, String gender, float score, int age)
    {
        this.set(id, name, gender, score, age);
    }

    public void set(String id, String name, String gender, float score, int age)
    {
        this.id = id == null ? "" : id;
        this.name = name == null ? "" : name;
        this.gender = gender == null ? "" : gender;
        this.score = score;
        this.age = age;
    }

    public String toString()
    {
        return this.id + " " + this.name + " " + this.gender + " " + this.age + " " + this.score;
    }
}
