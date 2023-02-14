str1 := "this is a [sample] [[string]] with [SOME] special words"

	re := regexp.MustCompile(`\[([^\[\]]*)\]`)
	fmt.Printf("Pattern: %v\n", re.String())      // print pattern
	fmt.Println("Matched:", re.MatchString(str1)) // true

	fmt.Println("\nText between square brackets:")
	submatchall := re.FindAllString(str1, -1)
	for _, element := range submatchall {
		element = strings.Trim(element, "[")
		element = strings.Trim(element, "]")
		fmt.Println(element)
	}
// match phone number
re := regexp.MustCompile(`^(?:(?:\(?(?:00|\+)([1-4]\d\d|[1-9]\d?)\)?)?[\-\.\ \\\/]?)?((?:\(?\d{1,}\)?[\-\.\ \\\/]?){0,})(?:[\-\.\ \\\/]?(?:#|ext\.?|extension|x)[\-\.\ \\\/]?(\d+))?$`)

