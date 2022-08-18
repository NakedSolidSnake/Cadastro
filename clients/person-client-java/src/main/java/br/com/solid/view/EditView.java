package br.com.solid.view;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import br.com.solid.controller.IController;
import br.com.solid.controller.PersonDTO;

//public class EditView extends JDialog{
public class EditView extends View{

	private static final long serialVersionUID = 1L;
	private Integer id;
	private IController controller;
	private PersonDTO dto;
	
	public EditView (String title, Integer id, IController controller) {
		this (title);
		this.id = id;
		this.controller = controller;
		dto = controller.getPersonBy(id);
		super.fillScreenFields (dto);
		super.setVisibleOn();
	}

	private EditView(String title) {
		super(title);
		super.addConfirmActionListener(new ConfirmAction());		
	}
	
	private class ConfirmAction implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			PersonDTO personDTO = getDataFromScreen ();
			try {
				controller.onUpdate (id, personDTO);
				dispose();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			dispose ();
		}
	}	
}
