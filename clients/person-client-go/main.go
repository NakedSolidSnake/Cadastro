package main

import (
	"fmt"
	"net/http"

	"github.com/person-client/routes"
)

func main() {
	routes.LoadRoutes()
	fmt.Println("Running on port 8009")
	http.ListenAndServe(":8009", nil)
}
