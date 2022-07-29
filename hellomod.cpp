package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"os"
	"strconv"

	"github.com/gocolly/colly"
)

func main() {

	fname := "data.csv"
	file, err := os.Create(fname)
	
	if err != nil {
		log.Fatalf("Could not create file, err : %q", err)
		return
	}

	defer file.Close()

	writer := csv.NewWriter(file)
	writer.Flush()

	c := colly.NewCollector(
		colly.AllowedDomains("internshala.com"),
	)

	c.OnHTML(".internship_meta", func(e *colly.HTMLElement){
		writer.Write([]string{
			e.ChildText("a"),
			e.ChildText("span"),

		})
	})

	for i:= 1; i <= 150; i++{
		fmt.Printf("Scraping page : %d\n", i)
		c.Visit("http://internshala.com/internships/page-" + strconv.Itoa(i))
	}

	log.Printf("SCRAPING COMPLETE MAN \n")
	log.Println(c)
}
