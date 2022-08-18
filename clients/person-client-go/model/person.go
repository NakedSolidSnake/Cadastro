package model

type Person struct {
	Id      int    `json:"id"`
	Name    string `json:"name"`
	Address string `json:"address"`
	Age     int64  `json:"age"`
}

type Persons struct {
	Persons []Person `json:"persons"`
}
