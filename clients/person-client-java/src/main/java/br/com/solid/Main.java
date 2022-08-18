package br.com.solid;
import java.io.IOException;

import br.com.solid.config.PersonClientProperties;
import br.com.solid.controller.Controller;
import br.com.solid.view.PersonView;

public class Main {
	@SuppressWarnings("unused")
	public static void main(String[] args) throws IOException {
		Controller controller = new Controller(new PersonView(new PersonClientProperties()), new PersonClientProperties());
	}
}
