package br.com.solid.controller;

import java.io.IOException;

public interface IController {

	void onAdd(PersonDTO personDTO) throws IOException ;

	void onUpdate(Integer id, PersonDTO personDTO) throws IOException ;

	void onDelete(int id) throws IOException ;
	
	void onLoad () throws IOException ;
	
	PersonDTO getPersonBy (Integer id);

}
