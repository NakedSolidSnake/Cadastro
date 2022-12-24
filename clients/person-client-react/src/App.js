import './App.css';
import Formulario from './Formulario';
import Tabela from './Tabela';
import { useEffect, useState } from 'react';

function App() {

  const url = "http://localhost:8080/persons";

  const person = {
    name : '',
    address: '',
    age: 0
  }

  const [btnCadastrar, setBtnCadastrar] = useState (true);
  const [persons, setPersons] = useState ([]);
  const [personObject, setObjectPerson] = useState (person);

  useEffect (
    () => {
      fetch (url)
      .then (response => response.json ())
      .then (data => setPersons (data.persons));
    }, [persons]
  );

  const onType = (event) => {
    if (event.target.name === 'age') {
       personObject.age = parseInt (event.target.value, 10);
    }
    else {
      setObjectPerson ({...personObject, [event.target.name]:event.target.value});
    }
  }

  const postPerson = () => {
    fetch (url, {
      method:'post',
      body: JSON.stringify (personObject),
      headers: {
        'Content-type' : 'application/json',
        'Accept' : 'application/json'
      }
    }).then (response => {
      if (response.status === 202) {
        alert ("New registry created");
        clearForm ();
      }
    })
    .catch (console.log ("Error"))
  }

  const deletePerson = () => {
    fetch (url + "?id=" + personObject.id, {
      method:'delete',
      headers: {
        'Content-type' : 'application/json',
        'Accept' : 'application/json'
      }
    }).then (response => {
      if (response.status === 200) {
        clearForm ();
        alert(personObject.name + " deleted");

      }
    })
    .catch (console.log ("Error"))
  }

  const updatePerson = () => {
    fetch (url + "?id=" + personObject.id, {
      method:'put',
      body: JSON.stringify (personObject),
      headers: {
        'Content-type' : 'application/json',
        'Accept' : 'application/json'
      }
    }).then (response => {
      if (response.status === 200) {
        alert("Object id: " + personObject.id + " updated");
        clearForm ();
      }
    })
    .catch (console.log ("Error"))
  }


  const selectPerson = (index) => {
    setObjectPerson (persons[index]);
    setBtnCadastrar (false);
  }

  const clearForm = () => {
    setObjectPerson (person);
    setBtnCadastrar (true);
  }

  return (
    <div>
      <Formulario botao={btnCadastrar} onType={onType} onPost={postPerson} object={personObject} cancel={clearForm} onDelete={deletePerson} onUpdate={updatePerson}/>
      <Tabela array={persons} select={selectPerson} />
    </div>
  );
}

export default App;
