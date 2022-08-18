package br.com.solid.config;

public interface IConfig {
	public void save (String address, String port);
	public String load ();
}
