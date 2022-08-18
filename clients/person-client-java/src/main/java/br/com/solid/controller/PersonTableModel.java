package br.com.solid.controller;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import br.com.solid.domain.Person;
import br.com.solid.domain.Persons;



public class PersonTableModel <T> extends AbstractTableModel{
	
	private static final long serialVersionUID = -1691811491265559179L;
	
	private final String[] columnNames = new String[] {
			"Id", "Name", "Address", "Age"
	};
	
	transient List<T>  persons = new ArrayList<T>();
	
	private static final int ID	 = 0;
	private static final int NAME 	 = 1;
	private static final int ADDRESS	 = 2;
	private static final int AGE	 = 3;
	
	public PersonTableModel() {
		super();
	}
	
	@Override
	public String getColumnName(int column)
	{
		return columnNames[column];
	}

	@Override
	public int getRowCount() {
		return persons.size();
	}

	@Override
	public int getColumnCount() {
		return columnNames.length;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		Person person = (Person)getElementAt(rowIndex);
		switch(columnIndex) {
		case ID:			
			return person.getId();
		case NAME:
			return person.getName();
		case ADDRESS:			
			return person.getAddress();
		case AGE:
			return person.getAge();
		

		default:
			return "";
		}		
	}
	
	public T getElementAt(int row) {
		return persons.get(row);
	}
	
	public PersonDTO getElementDTOAt(int row) {
		Person person = (Person)persons.get(row);
		return new PersonDTO(person.getName(), person.getAddress(), person.getAge().toString());
	}
	
	@SuppressWarnings("unchecked")
	public void addAll (Persons persons2) {
		persons.clear();
		persons.addAll((Collection<? extends T>) persons2.getPersons());
		this.fireTableDataChanged();
	}
	
	public void setAll(List<T> pol){
		persons.clear();
		persons.addAll(pol);
		fireUpdateEvent();
	}
	
	public void fireUpdateEvent() {
        fireTableDataChanged();
    }
	
	public void removeElementAt(int row) {
    	try {
	        persons.remove(row);	        
	        this.fireTableDataChanged();
    	}
	    catch (Exception e)
	    {
				
		}	        
    }
}
