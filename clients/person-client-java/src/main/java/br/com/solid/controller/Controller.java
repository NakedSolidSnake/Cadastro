package br.com.solid.controller;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

import org.apache.hc.client5.http.classic.methods.HttpPost;
import org.apache.hc.client5.http.impl.classic.CloseableHttpClient;
import org.apache.hc.client5.http.impl.classic.CloseableHttpResponse;
import org.apache.hc.client5.http.impl.classic.HttpClients;
import org.apache.hc.core5.http.io.entity.StringEntity;

import com.google.gson.Gson;

import br.com.solid.config.PersonClientProperties;
import br.com.solid.domain.Person;
import br.com.solid.domain.Persons;

public class Controller implements IController{
	
	private Persons persons;
	private IView view;
	private PersonTableModel<Person> personsTableModel = new PersonTableModel<Person>();
	private String path;
	
		
	public Controller(IView view, PersonClientProperties properties) {		
		String[] split = properties.load().split(",");
		String url = split[0];
		String port = split[1];
		path = url + ":" + port + "/persons";
		this.view = view;			
		this.view.setModel(personsTableModel);
		this.view.setController(this);		
	}
	
	@Override
	public void onAdd(PersonDTO personDTO) throws IOException{
		Person person = personDTO.convertToDomain(personDTO);
		
		CloseableHttpClient client = HttpClients.createDefault();
	    HttpPost httpPost = new HttpPost(path);

	    Gson gson = new Gson();	    
	    
	    String json = gson.toJson(person);
	    StringEntity entity = new StringEntity(json);
	    httpPost.setEntity(entity);
	    httpPost.setHeader("Accept", "application/json");
	    httpPost.setHeader("Content-type", "application/json");

	    CloseableHttpResponse response = client.execute(httpPost);
	    if (response.getCode() == 200 || response.getCode() == 201) {
	    	System.out.println("Created");
	    }
	    client.close();
	}

	@Override
	public void onUpdate(Integer id, PersonDTO personDTO) throws IOException{
		Person person = personDTO.convertToDomain(personDTO);
		
		URL url = new URL(path + "?id=" + id);
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		con.setRequestMethod("PUT");
		con.setInstanceFollowRedirects(false);	
		con.setDoOutput(true);
		
		DataOutputStream out = new DataOutputStream(con.getOutputStream());
		
		Gson gson = new Gson();
		
		
		out.writeBytes(gson.toJson(person));
		out.flush();
		out.close();
		
		int status = con.getResponseCode();
		
		if (status == HttpURLConnection.HTTP_MOVED_TEMP || status == HttpURLConnection.HTTP_MOVED_PERM) {
			String location = con.getHeaderField("Location");
			URL newUrl = new URL(location);
			con = (HttpURLConnection) newUrl.openConnection();
		}
		
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer content = new StringBuffer();
		while ((inputLine = in.readLine()) != null) {
			content.append(inputLine);
		}
		
		System.out.println(content);
		
		in.close();
		
		con.disconnect();
	}

	@Override
	public void onDelete(int id) throws IOException{
		// TODO Auto-generated method stub
		URL url = new URL(path + "?id=" + id);
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		con.setRequestMethod("DELETE");
		con.setInstanceFollowRedirects(false);
		
		int status = con.getResponseCode();
		
		if (status == HttpURLConnection.HTTP_MOVED_TEMP || status == HttpURLConnection.HTTP_MOVED_PERM) {
			String location = con.getHeaderField("Location");
			URL newUrl = new URL(location);
			con = (HttpURLConnection) newUrl.openConnection();
		}
		
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer content = new StringBuffer();
		while ((inputLine = in.readLine()) != null) {
			content.append(inputLine);
		}
		
		System.out.println(content);
		
		in.close();
		
		con.disconnect();
	}

	@Override
	public void onLoad() throws IOException {
		URL url = new URL(path);
		HttpURLConnection con = (HttpURLConnection) url.openConnection();
		con.setRequestMethod("GET");
		con.setInstanceFollowRedirects(false);		
		
		int status = con.getResponseCode();
		
		if (status == HttpURLConnection.HTTP_MOVED_TEMP || status == HttpURLConnection.HTTP_MOVED_PERM) {
			String location = con.getHeaderField("Location");
			URL newUrl = new URL(location);
			con = (HttpURLConnection) newUrl.openConnection();
		}
		
		BufferedReader in = new BufferedReader(new InputStreamReader(con.getInputStream()));
		String inputLine;
		StringBuffer content = new StringBuffer();
		while ((inputLine = in.readLine()) != null) {
			content.append(inputLine);
		}
		
		System.out.println(content);
		
		Gson gson = new Gson();
		this.persons = gson.fromJson(content.toString(), Persons.class);
		personsTableModel.addAll(persons);
		
		in.close();
		
		con.disconnect();
	}

	@Override
	public PersonDTO getPersonBy(Integer id) {
		Person person = this.persons.getPersons().get(id);
		return new PersonDTO(person.getName(), person.getAddress(), person.getAge().toString());
	}
}
