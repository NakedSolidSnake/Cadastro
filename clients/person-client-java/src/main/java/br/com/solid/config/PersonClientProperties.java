package br.com.solid.config;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Properties;

public class PersonClientProperties implements IConfig{
	
	private void saveProperties (String address, String port) {
		 try (OutputStream output = new FileOutputStream("/home/cssouza/java_examples/person-client/src/main/resources/properties.properties")) {

	            Properties prop = new Properties();

	            // set the properties value
	            prop.setProperty("server.ip", address);
	            prop.setProperty("server.port", port);

	            // save properties to project root folder
	            prop.store(output, null);

	            System.out.println(prop);

	        } catch (IOException io) {
	            io.printStackTrace();
	        }
	}
	
	private String loadProperties () {
		String config = "";
		String address = "";
		String port = "";
		
		try (InputStream input = new FileInputStream("/home/cssouza/java_examples/person-client/src/main/resources/properties.properties")) {

            Properties prop = new Properties();

            prop.load(input);
            
            address = prop.getProperty("server.ip", null);
            port = prop.getProperty("server.port", null);
            
            config = address + "," + port;

        } catch (IOException ex) {
            ex.printStackTrace();
        }
		
		return config;
	}

	@Override
	public void save(String address, String port) {
		saveProperties(address, port);
	}

	@Override
	public String load() {
		// TODO Auto-generated method stub
		return loadProperties();
	}
}
