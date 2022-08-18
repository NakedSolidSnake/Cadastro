package br.com.solid.controller;

import br.com.solid.domain.Person;

public interface IView {

	void setModel (PersonTableModel<Person> model);	
	void setController (IController controller);
}
