package main

import (
    "fmt"
    "time"

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

type Article struct {
    ID    uint
    Title string
    Tags  []Tag `gorm:"many2many:article_tags"`
}

type Tag struct {
    ID   uint
    Name string
}

type ArticleTag struct {
    ArticleID uint `gorm:"primaryKey"`
    TagID     uint `gorm:"primaryKey"`
    CreatedAt time.Time
}

func checkErr(err error) {
    if err != nil {
        panic(err)
    }
}
func main() {
    err := DB.SetupJoinTable(&Article{}, "Tags", &ArticleTag{})
    if err != nil {
        panic(err)
    }
    err = DB.AutoMigrate(&Article{}, &Tag{}, &ArticleTag{})
    if err != nil {
        panic(err)
    }
    err = DB.Create(&Article{
        Title: "language",
        Tags: []Tag{
            {Name: "Golang"},
            {Name: "Python"},
            {Name: "C++"},
        },
    }).Error
    if err != nil {
        panic(err)
    }

    // 添加文章，关联已有标签
    var tags []Tag
    DB.Find(&tags, "name in ?", []string{"C++", "Python"})
    err = DB.Create(&Article{
        Title: "others",
        Tags:  tags,
    }).Error
    checkErr(err)

    // 给已有文章关联标签
    article := Article{
        Title: "base",
    }
    DB.Create(&article)
    var at Article
    tags = tags[:0]
    DB.Find(&tags, "name in ?", []string{"C++", "Python"})
    err = DB.Take(&at, article.ID).Association("Tags").Append(tags)
    checkErr(err)

    // 替换已有文章的标签
    article = Article{}
    tags = tags[:0]
    DB.Find(&tags, "name in ?", []string{"后端"})
    DB.Take(&article, "title = ?", "others")
    err = DB.Model(&article).Association("Tags").Replace(tags)
    checkErr(err)

    // 查询文章列表，显示标签
    var articles []Article
    err = DB.Preload("Tags").Find(&articles).Error
    checkErr(err)
    fmt.Println(articles)
}
