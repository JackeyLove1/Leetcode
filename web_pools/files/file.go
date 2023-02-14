package main
import "os"

// rename a file 
err := os.Rename(oldName, newName)

// create an empty file 
emptyFile, err := os.Create("empty.txt")

// create directory
_, err := os.Stat("test")
 
if os.IsNotExist(err) {
	errDir := os.MkdirAll("test", 0755)
	if errDir != nil {
		log.Fatal(err)
	}
}
 
// copy file 
sourceFile, err := os.Open("/var/www/html/src/test.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer sourceFile.Close()
 
	// Create new file
	newFile, err := os.Create("/var/www/html/test.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer newFile.Close()
 
	bytesCopied, err := io.Copy(newFile, sourceFile)
	if err != nil {
		log.Fatal(err)
	}

// getting file meta

fileStat, err := os.Stat("test.txt")
 
	if err != nil {
		log.Fatal(err)
	}
 
	fmt.Println("File Name:", fileStat.Name())        // Base name of the file
	fmt.Println("Size:", fileStat.Size())             // Length in bytes for regular files
	fmt.Println("Permissions:", fileStat.Mode())      // File mode bits
	fmt.Println("Last Modified:", fileStat.ModTime()) // Last modification time
	fmt.Println("Is Directory: ", fileStat.IsDir())   // Abbreviation for Mode().IsDir()

// delete file 
err := os.Remove("/var/www/html/test.txt")

// read file character by character
filename := "test.txt"
 
	filebuffer, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	inputdata := string(filebuffer)
	data := bufio.NewScanner(strings.NewReader(inputdata))
	data.Split(bufio.ScanRunes)
 
	for data.Scan() {
		fmt.Print(data.Text())
	}

// truncate
err := os.Truncate("test.txt", 100)

// append file 
message := "Add this content at end"
	filename := "test.txt"
 
	f, err := os.OpenFile(filename, os.O_RDWR|os.O_APPEND|os.O_CREATE, 0660)
 
	if err != nil {
		fmt.Println(err)
		os.Exit(-1)
	}
	defer f.Close()
 
	fmt.Fprintf(f, "%s\n", message)

// change file meta
// Test File existence.
_, err := os.Stat("test.txt")
if err != nil {
	if os.IsNotExist(err) {
		log.Fatal("File does not exist.")
	}
}
log.Println("File exist.")

// Change permissions Linux.
err = os.Chmod("test.txt", 0777)
if err != nil {
	log.Println(err)
}

// Change file ownership.
err = os.Chown("test.txt", os.Getuid(), os.Getgid())
if err != nil {
	log.Println(err)
}

// Change file timestamps.
addOneDayFromNow := time.Now().Add(24 * time.Hour)
lastAccessTime := addOneDayFromNow
lastModifyTime := addOneDayFromNow
err = os.Chtimes("test.txt", lastAccessTime, lastModifyTime)
if err != nil {
	log.Println(err)
}

// compress file into zip
func appendFiles(filename string, zipw *zip.Writer) error {
	file, err := os.Open(filename)
	if err != nil {
		return fmt.Errorf("Failed to open %s: %s", filename, err)
	}
	defer file.Close()
 
	wr, err := zipw.Create(filename)
	if err != nil {
		msg := "Failed to create entry for %s in zip file: %s"
		return fmt.Errorf(msg, filename, err)
	}
 
	if _, err := io.Copy(wr, file); err != nil {
		return fmt.Errorf("Failed to write %s to zip: %s", filename, err)
	}
 
	return nil
}
 
func main() {
	flags := os.O_WRONLY | os.O_CREATE | os.O_TRUNC
	file, err := os.OpenFile("test.zip", flags, 0644)
	if err != nil {
		log.Fatalf("Failed to open zip for writing: %s", err)
	}
	defer file.Close()
 
	var files = []string{"test1.txt", "test2.txt", "test3.txt"}
 
	zipw := zip.NewWriter(file)
	defer zipw.Close()
 
	for _, filename := range files {
		if err := appendFiles(filename, zipw); err != nil {
			log.Fatalf("Failed to add file %s to zip: %s", filename, err)
		}
	}
}

// unzip
zipReader, _ := zip.OpenReader("test.zip")
	for _, file := range zipReader.Reader.File {
 
		zippedFile, err := file.Open()
		if err != nil {
			log.Fatal(err)
		}
		defer zippedFile.Close()
 
		targetDir := "./"
		extractedFilePath := filepath.Join(
			targetDir,
			file.Name,
		)
 
		if file.FileInfo().IsDir() {
			log.Println("Directory Created:", extractedFilePath)
			os.MkdirAll(extractedFilePath, file.Mode())
		} else {
			log.Println("File extracted:", file.Name)
 
			outputFile, err := os.OpenFile(
				extractedFilePath,
				os.O_WRONLY|os.O_CREATE|os.O_TRUNC,
				file.Mode(),
			)
			if err != nil {
				log.Fatal(err)
			}
			defer outputFile.Close()
 
			_, err = io.Copy(outputFile, zippedFile)
			if err != nil {
				log.Fatal(err)
			}
		}
	}

// write text file 
sampledata := []string{"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
		"Nunc a mi dapibus, faucibus mauris eu, fermentum ligula.",
		"Donec in mauris ut justo eleifend dapibus.",
		"Donec eu erat sit amet velit auctor tempus id eget mauris.",
	}
 
	file, err := os.OpenFile("test.txt", os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
 
	if err != nil {
		log.Fatalf("failed creating file: %s", err)
	}
 
	datawriter := bufio.NewWriter(file)
 
	for _, data := range sampledata {
		_, _ = datawriter.WriteString(data + "\n")
	}
 
	datawriter.Flush()
	file.Close()

// read csv
file, err := os.Open("test.txt")
 
	if err != nil {
		log.Fatalf("failed opening file: %s", err)
	}
 
	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)
	var txtlines []string
 
	for scanner.Scan() {
		txtlines = append(txtlines, scanner.Text())
	}
 
	file.Close()
 
	for _, eachline := range txtlines {
		fmt.Println(eachline)
	}

// 