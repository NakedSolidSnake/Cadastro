package main

import (
	"net/http"

	"github.com/person-client/routes"
)

func main() {
	routes.LoadRoutes()
	http.ListenAndServe(":8009", nil)
}
