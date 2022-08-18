package br.com.solid.domain;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Person {

	@Expose
	@SerializedName ("id")
	String id;
	
	@Expose
	@SerializedName ("name")	
	String name;
	
	@Expose
	@SerializedName ("address")
	String address;
	
	@Expose
	@SerializedName ("age")
	Integer age;
	
	public Person(String name, String address, Integer age) {
		this.name = name;
		this.address = address;
		this.age = age;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getAddress() {
		return address;
	}

	public void setAddress(String address) {
		this.address = address;
	}

	public Integer getAge() {
		return age;
	}

	public void setAge(Integer age) {
		this.age = age;
	}
	
}
