package br.com.solid.controller;

import br.com.solid.domain.Person;

public class PersonDTO {
	private String name;
	private String address;
	private String age;
	
	public PersonDTO(String name, String address, String age) {
		this.name = name;
		this.address = address;
		this.age = age;
	}
	
	public Person convertToDomain (PersonDTO dto) {
		return new Person (name, address, Integer.parseInt(age));
	}

	public String getName() {
		return name;
	}

	public String getAddress() {
		return address;
	}

	public String getAge() {
		return age;
	}
	
	public PersonDTO convertToDTO (Person person) {
		return new PersonDTO(person.getName(), person.getAddress(), person.getAge().toString());
	}
}
