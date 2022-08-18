package br.com.solid.domain;

import java.util.ArrayList;
import java.util.List;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class Persons {

	@Expose
	@SerializedName ("persons")
	List<Person> persons = new ArrayList<Person>();

	public List<Person> getPersons() {
		return new ArrayList<Person>(this.persons);
	}

	public void setPersons(Person person) {
		this.persons.add(person);
	}
		
}
