package br.com.solid.view;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;

import br.com.solid.config.IConfig;
import br.com.solid.controller.IController;
import br.com.solid.controller.IView;
import br.com.solid.controller.PersonTableModel;
import br.com.solid.domain.Person;

public class PersonView extends JFrame implements IView{
	
	private static final long serialVersionUID = 6165233651666895872L;
	private static Integer WINDOW_WIDTH = 800;
	private static Integer WINDOW_HEIGHT = 600;
	
	JTextField tfServerAddress = new JTextField();
	JTextField tfServerPort = new JTextField();
	JButton btSave = new JButton ("Save");
	private IConfig config;
	private IController controller;
	
	JButton btAdd = new JButton ("Add");
	JButton btEdit = new JButton ("Edit");
	JButton btDelete = new JButton ("Delete");
	
	JTable table = new JTable();
	
	public PersonView(IConfig config) {
		this.config = config;
		createView ();
		addListerners ();
		loadConf ();		
	}
	
	private void loadConf() {
		String load = config.load();
		String[] params = load.split(",");
		
		tfServerAddress.setText(params[0]);
		tfServerPort.setText(params[1]);
	}

	private void addListerners() {
		btSave.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				config.save(tfServerAddress.getText(), tfServerPort.getText());
			}
		});	
		
		btAdd.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				new AddView ("Add new User", controller);
				onLoad ();
			}
		});
		
		btEdit.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				if (isSelected()) {
					int id = getIndexFromTable ();
					new EditView ("Edit User", id, controller);
					onLoad ();
				}
			}
		});
		
		btDelete.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				if (isSelected()) {
					try {
						controller.onDelete (getIndexFromTable ());
						onLoad ();
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				}
			}
		});
	}

	private void createView() {
		JPanel panel = new JPanel(new BorderLayout(10, 10));
		this.setTitle("Person Client Java");
		this.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		
		panel.setBorder(new EmptyBorder(10, 10, 10, 10));
		this.add(panel);
		
		panel.add(createPageStart (), BorderLayout.PAGE_START);
		panel.add(createTablePanel (), BorderLayout.CENTER);
		panel.add(createButtons (), BorderLayout.PAGE_END);
		setVisible(true);
	}

	private JPanel createButtons() {
		
		JPanel panel = new JPanel (new FlowLayout());
		
		panel.add(btAdd);
		panel.add(btEdit);
		panel.add(btDelete);
		
		return panel;
	}

	private Component createTablePanel() {
		table.getTableHeader().setReorderingAllowed(false);
		table.getTableHeader().setResizingAllowed(false);
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		JScrollPane scrollPane = new JScrollPane(table);
		return scrollPane;
	}

	private JPanel createPageStart() {
		JPanel panel = new JPanel(new FlowLayout());
		panel.add (new JLabel("Host address: "));
		
		tfServerAddress.setPreferredSize(new Dimension(200, 25));		
		tfServerPort.setPreferredSize(new Dimension(50, 25));		
		
		panel.add(tfServerAddress);
		panel.add (new JLabel("Port: "));
		panel.add(tfServerPort);
		panel.add(btSave);
		return panel;
	}

	@Override
	public void setModel(PersonTableModel<Person> model) {
		table.setModel(model);
	}
	
	private boolean isSelected () {
		boolean status = true;
		
		int line = table.getSelectedRow();
		if ((line < 0) || (line >= table.getModel().getRowCount())) {
			status = false;
		}
		
		return status;		
	}
	
	private int getIndexFromTable () {
		int line = table.getSelectedRow();
		return table.convertRowIndexToModel(line);
	}
	
	
	@Override
	public void setController(IController controller) {
		this.controller = controller; 
		onLoad ();
	}
	
	private void onLoad () {
		try {
			this.controller.onLoad();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
