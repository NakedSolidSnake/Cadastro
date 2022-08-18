package controller

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"strconv"
	"text/template"

	"github.com/person-client/model"
)

var templates = template.Must(template.ParseGlob("templates/*.html"))
var PersonsList model.Persons

func Index(w http.ResponseWriter, r *http.Request) {

	PersonsList = getAllPersons()
	fmt.Println(PersonsList)
	templates.ExecuteTemplate(w, "Index", PersonsList.Persons)
}

func getAllPersons() model.Persons {
	response, err := http.Get("http://localhost:8080/persons")
	if err != nil {
		log.Fatalln(err)
	}
	//We Read the response body on the line below.
	var persons model.Persons
	body, _ := ioutil.ReadAll(response.Body)
	json.Unmarshal([]byte(body), &persons)

	return persons
}

func New(w http.ResponseWriter, r *http.Request) {

	templates.ExecuteTemplate(w, "New", nil)
}

func Insert(w http.ResponseWriter, r *http.Request) {

	if r.Method == "POST" {
		name := r.FormValue("name")
		address := r.FormValue("address")
		age := r.FormValue("age")

		body, _ := json.Marshal(map[string]string{
			"name":    name,
			"address": address,
			"age":     age,
		})

		payload := bytes.NewBuffer(body)

		_, err := http.Post("http://localhost:8080/persons", "application/json", payload)
		if err != nil {
			log.Fatalln(err)
		}

	}

	http.Redirect(w, r, "/", 301)
}

func Delete(w http.ResponseWriter, r *http.Request) {
	id := r.URL.Query().Get("id")

	var client = &http.Client{}

	req, err := http.NewRequest(http.MethodDelete, "http://localhost:8080/persons", nil)
	if err != nil {
		log.Fatalln(err)
	}
	req.Header.Add("Content-Type", "application/json")
	query := req.URL.Query()
	query.Add("id", id)
	req.URL.RawQuery = query.Encode()

	_, err = client.Do(req)
	if err != nil {
		log.Fatalln(err)
	}

	http.Redirect(w, r, "/", 301)
}

func Edit(w http.ResponseWriter, r *http.Request) {
	id := r.URL.Query().Get("id")
	idConverter, _ := strconv.ParseInt(id, 0, 32)

	person := PersonsList.Persons[idConverter]
	person.Id = int(idConverter)
	templates.ExecuteTemplate(w, "Edit", person)
}

func Update(w http.ResponseWriter, r *http.Request) {
	if r.Method == "POST" {
		fmt.Println("PUT")
		id := r.FormValue("id")
		name := r.FormValue("name")
		address := r.FormValue("address")
		age := r.FormValue("age")

		idConvert, err := strconv.Atoi(id)
		if err != nil {
			log.Println("ID Conversion error: ", err)
		}

		ageConv, err := strconv.Atoi(age)
		if err != nil {
			log.Println("ID Conversion error: ", err)
		}

		person := model.Person{Id: idConvert, Name: name, Address: address, Age: int64(ageConv)}

		body, _ := json.Marshal(person)
		payload := bytes.NewBuffer(body)

		req, err := http.NewRequest(http.MethodPut, "http://localhost:8080/persons", payload)
		if err != nil {
			log.Fatalln(err)
		}

		req.Header.Add("Content-Type", "application/json")
		query := req.URL.Query()
		query.Add("id", id)
		req.URL.RawQuery = query.Encode()

		var client = &http.Client{}
		_, err = client.Do(req)
		if err != nil {
			log.Fatalln(err)
		}
	}
	http.Redirect(w, r, "/", 301)
}
