package br.com.solid.view;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import br.com.solid.controller.IController;
import br.com.solid.controller.PersonDTO;

public class AddView extends View{

	private static final long serialVersionUID = -6416510774635295747L;
	private IController controller;

	public AddView (String title, IController controller) {
		super(title);
		this.controller = controller;
		super.addConfirmActionListener(new ConfirmAction());
		super.setVisibleOn();
	}
	
	private class ConfirmAction implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			PersonDTO personDTO = getDataFromScreen ();
			try {
				controller.onAdd (personDTO);
				dispose();
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}		
	}
}
