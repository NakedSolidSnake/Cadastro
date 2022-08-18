class Person {
    id;
    name;
    address;
    age;
}

function getPersonFromScreen(person) {
    person.name = document.getElementById("fname").value;
    document.getElementById("fname").value = "";

    person.address = document.getElementById("faddress").value;
    document.getElementById("faddress").value = "";

    person.age = parseFloat(document.getElementById("fage").value);
    document.getElementById("fage").value = "";
}

function getPersonJSON (object) {
    alert (JSON.stringify(object));
    return JSON.stringify(object);
}

function httpSendData() {

    person = new Person();
    getPersonFromScreen(person);            

    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function () {
        if (xmlHttp.readyState == 4 && (xmlHttp.status == 202 || xmlHttp.status == 201)){
            window.location.replace('/');
        }
    }

    xmlHttp.open("POST", "/persons", true); // true for asynchronous 
    xmlHttp.setRequestHeader("Content-Type", "application/json");
    xmlHttp.send(getPersonJSON (person));
}

function returnHome(){
    window.location.replace('/');
}

var row_selected;

function clearSelection(){
    var table = document.getElementById('myTable');
    var rows = table.querySelectorAll('tr');

    for(var i = 0; i < rows.length; i++){
        rows[i].classList.remove('highlight'); 
    }
}

function httpSendData(id) {                            

    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function () {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200){
            window.location.replace('/');
        }
    }

    xmlHttp.open("DELETE", "/persons", false); // true for asynchronous 
    xmlHttp.setRequestHeader("Content-Type", "application/json");
    xmlHttp.send("id="+ id);
}

function getSelectedRow(){

    if(row_selected != null){
        
    }else{
        alert("Select a registry to delete");
        return;
    }

    id = row_selected.cells[0].innerHTML;
    
    return id;
}

function sendDelete(){
    httpSendData(getSelectedRow());
}


function getSelectedRowPerson(){

    if(row_selected != null){
        
    }else{
        alert("Please select a registry to edit");
        return;
    }

    person = new Person();

    person.id = row_selected.cells[0].innerHTML;
    person.name = row_selected.cells[1].innerHTML;
    person.address = row_selected.cells[2].innerHTML;
    person.age = row_selected.cells[3].innerHTML;

    return person;
}

function storePerson(person){
    // Check browser support
    if (typeof(Storage) !== "undefined") {
    // Store
        localStorage.setItem("id", person.id);
        localStorage.setItem("name", person.name);
        localStorage.setItem("address", person.address);
        localStorage.setItem("age", person.age);
    }
}

function sendEdit(){
    person = getSelectedRowPerson();
    storePerson(person)
    window.location.replace('/edit.html');
}

function sendNew(){
    window.location.replace('/new.html');
}
