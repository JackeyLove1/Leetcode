package main

import (
    "fmt"

    "gorm.io/driver/mysql"
    "gorm.io/gorm"
    "gorm.io/gorm/logger"
)

const (
    username = "root"
    password = ""
    host     = "127.0.0.1"
    port     = 3306
    dbname   = "gorm"
    timeout  = "10s"
)

var DB *gorm.DB
var mysqlLogger logger.Interface

func getGormConfig() *gorm.Config {
    mysqlLogger = logger.Default.LogMode(logger.Info)
    return &gorm.Config{
        SkipDefaultTransaction: true,
    }
}

func init() {
    dsn := fmt.Sprintf("%s:%s@tcp(%s:%d)/%s?charset=utf8mb4&parseTime=True&loc=Local&timeout=%s",
        username, password, host, port, dbname, timeout)
    db, err := gorm.Open(mysql.Open(dsn), getGormConfig())
    if err != nil {
        panic("failed to connect to db, err" + err.Error())
    }
    DB = db
    fmt.Println("connect db success")
    DB = DB.Session(&gorm.Session{
        Logger: mysqlLogger,
    })
}

type User struct {
    ID       uint
    Name     string `gorm:"size:8"`
    Articles []Article
}

type Article struct {
    ID     uint
    Title  string `gorm:"size:16"`
    UserID uint   // 属于
    User   *User
}

func main() {
    err := DB.AutoMigrate(&User{}, &Article{})
    if err != nil {
        panic(err)
    }
    a1 := Article{Title: "python"}
    a2 := Article{Title: "golang"}
    user := User{Name: "Jacky", Articles: []Article{a1, a2}}
    err = DB.Create(&user).Error
    if err != nil {
        panic(err)
    }
}
