package br.com.solid.view;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.NumberFormat;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.text.NumberFormatter;

import br.com.solid.controller.PersonDTO;

public abstract class View extends JDialog{
	private static final long serialVersionUID = 1L;
	JTextField tfName = new JTextField();
	JTextField tfAddress = new JTextField();
	JFormattedTextField tfAge;
	
	JButton btConfirm = new JButton ("Confirm");
	JButton btCancel = new JButton ("Cancel");
	private String title;
	
	public View (String title) {
		this.title = title;
		settingComponents ();
		addListeners ();
		componentSInitialState ();
		createView ();		
	}	

	private void componentSInitialState() {
		btConfirm.setEnabled(false);
	}

	private void addListeners() {
		btCancel.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				dispose();
			}
		});
		
		tfName.addCaretListener(new ContentVerify(tfName));
		tfAddress.addCaretListener(new ContentVerify(tfAddress));
		tfAge.addCaretListener(new ContentVerify(tfAge));
	}

	private void settingComponents() {		
		
		NumberFormat format = NumberFormat.getInstance();
	    NumberFormatter formatter = new NumberFormatter(format);
	    formatter.setValueClass(Integer.class);
	    formatter.setMinimum(-1);
	    formatter.setMaximum(120);
	    formatter.setAllowsInvalid(false);
	    // If you want the value to be committed on each keystroke instead of focus lost
	    formatter.setCommitsOnValidEdit(true);
	    
	    tfAge = new JFormattedTextField(formatter);
	    
	    tfName.setPreferredSize(new Dimension(300, 22));
		tfAddress.setPreferredSize(new Dimension(300, 22));
		tfAge.setPreferredSize(new Dimension(40, 22));
	}

	private void createView() {
		JPanel panel = new JPanel ();
		this.setTitle(title);
		this.add(panel);
		panel.add(createContent ());
		
		this.setSize(400, 200);
		this.setLocationRelativeTo(null);		
	}

	private JPanel createContent() {
		JPanel panel = new JPanel (new GridBagLayout());
		panel.setBorder(new EmptyBorder(10, 10, 10, 10));
		
		JLabel lbName = new JLabel("Name: ");
		JLabel lbAddress = new JLabel("Address: ");
		JLabel lbAge = new JLabel("Age: ");		
		
		panel.add(lbName, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE,
				new Insets(5, 5, 5, 0), 0, 0));
		panel.add(tfName, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH,
				new Insets(5, 5, 5, 0), 0, 0));
		
		panel.add(lbAddress, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE,
				new Insets(5, 5, 5, 0), 0, 0));
		panel.add(tfAddress, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH,
				new Insets(5, 5, 5, 0), 0, 0));
		
		panel.add(lbAge, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE,
				new Insets(5, 5, 5, 0), 0, 0));
		panel.add(tfAge, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE,
				new Insets(5, 5, 5, 0), 0, 0));
		
		panel.add(createButtons(), new GridBagConstraints(0, 4, 2, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH,
				new Insets(5, 5, 5, 0), 0, 0));
		
		return panel;
	}

	private JPanel createButtons() {
		JPanel panel = new JPanel(new FlowLayout());
		panel.add(btConfirm);
		panel.add(btCancel);
		return panel;
	}
	
	public void addConfirmActionListener (ActionListener listener) {
		btConfirm.addActionListener(listener);
	}
	
	public void setVisibleOn () {
		this.setModal(true);		
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		this.setVisible(true);
	}
	
	private class ContentVerify implements CaretListener {
		
		private JTextField field;
		private Border defaultBorder;

		public ContentVerify(JTextField field) {
			this.field = field;
			defaultBorder = field.getBorder();
		}

		@Override
		public void caretUpdate(CaretEvent e) {
			setConfirmEnable(false);
			if (field.getText().isEmpty()) {
				field.setBorder(new LineBorder(Color.RED, 2));
			} else {
				field.setBorder(defaultBorder);				
				if (isAllFieldsFilledProperly ()) {
					setConfirmEnable (true);
				} 
			}
		}		
	}
	
	private boolean isAllFieldsFilledProperly () {
		boolean status = true;
		status &= !tfName.getText().isEmpty();
		status &= !tfAddress.getText().isEmpty();
		status &= !tfAge.getText().isEmpty();
		
		return status;
	}
	
	private void setConfirmEnable (boolean status) {
		btConfirm.setEnabled(status);
	}
	
	public PersonDTO getDataFromScreen () {
		return new PersonDTO(tfName.getText(), tfAddress.getText(), tfAge.getText());
	}

	public void fillScreenFields(PersonDTO dto) {
		tfName.setText(dto.getName());
		tfAddress.setText(dto.getAddress());
		tfAge.setText(dto.getAge());		
		
	}
}
