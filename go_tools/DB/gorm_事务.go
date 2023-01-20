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
        // SkipDefaultTransaction: true,
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
    ID    uint   `json:"id"`
    Name  string `json:"name" gorm:"size:18"`
    Money uint   `json:"money" gorm:"size:32"`
}

func checkErr(err error) {
    if err != nil {
        panic(err)
    }
}
func main() {
    err := DB.AutoMigrate(&User{})
    checkErr(err)

    name1 := "jacky"
    DB.Create(&User{
        Name:  name1,
        Money: 1000,
    })
    name2 := "apple"
    DB.Create(&User{
        Name:  name2,
        Money: 2000,
    })

    var user1 User
    err = DB.Take(&user1, "name = ?", name1).Error
    checkErr(err)
    var user2 User
    err = DB.Take(&user2, "name = ?", name2).Error
    checkErr(err)

    // start transaction
    const trans = 100
    err = DB.Transaction(func(tx *gorm.DB) error {
        user1.Money -= trans
        err = DB.Model(&user1).Update("Money", user1.Money).Error
        if err != nil {
            return err
        }

        user2.Money += trans
        err = DB.Model(&user2).Update("Money", user2.Money).Error
        if err != nil {
            return err
        }
        return nil
    })
    checkErr(err)

}


/*
type User struct {
	ID    uint   `json:"id"`
	Name  string `json:"name"`
	Money int    `json:"money"`
  }
  
  // InnoDB引擎才支持事务，MyISAM不支持事务
  // DB.Set("gorm:table_options", "ENGINE=InnoDB").AutoMigrate(&User{})

  
  // simple transaction
  var zhangsan, lisi User
DB.Take(&zhangsan, "name = ?", "张三")
DB.Take(&lisi, "name = ?", "李四")
// 张三给李四转账100元
// 先给张三-100
zhangsan.Money -= 100
DB.Model(&zhangsan).Update("money", zhangsan.Money)
// 模拟失败的情况

// 再给李四+100
lisi.Money += 100
DB.Model(&lisi).Update("money", lisi.Money)


// munal transaction
// 开始事务
tx := db.Begin()

// 在事务中执行一些 db 操作（从这里开始，您应该使用 'tx' 而不是 'db'）
tx.Create(...)

// ...

// 遇到错误时回滚事务
tx.Rollback()

// 否则，提交事务
tx.Commit()

*/