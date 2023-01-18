package main

import (
    "encoding/json"
    "fmt"
    "math/rand"
    "strconv"

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
    paces    = 1
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
}

type Product struct {
    gorm.Model
    Code  string `json:"code" gorm:"type:varchar(12);column:code;default:0"`
    Price uint   `json:"price" gorm:"type:uint;column:price;default:0"`
}

// HookFunction
func (p *Product) BeforeCreate(tx *gorm.DB) (err error) {
    p.Code = "D011"
    return nil
}

func main() {
    // 开启日志
    DB = DB.Session(&gorm.Session{
        Logger: mysqlLogger,
    })
    // 迁移 schema
    err := DB.AutoMigrate(&Product{})
    if err != nil {
        panic("AutoMigrate Model Failed")
    }
    fmt.Println("AutoMigrate Model Success")

    // 插入
    err = DB.Create(&Product{Code: "D1", Price: 100}).Error
    if err != nil {
        panic("Insert Error " + err.Error())
    }

    // 批量插入
    products := make([]Product, 0, 10)
    for i := 0; i < paces; i++ {
        products = append(products, Product{
            Code:  "D" + strconv.Itoa(rand.Int()%100),
            Price: uint(i * 100),
        })
    }
    err = DB.Create(&products).Error
    if err != nil {
        panic(err)
    }

    // 单条记录查询
    var product1 Product
    err = DB.Take(&product1).Error
    if err != nil {
        panic(err)
    }
    fmt.Printf("product1 take: %+#v\n", product1)
    product1 = Product{}
    err = DB.First(&product1).Error
    if err != nil {
        panic(err)
    }
    fmt.Printf("product1 first: %+#v\n", product1)
    product1 = Product{}
    err = DB.Last(&product1).Error
    if err != nil {
        panic(err)
    }
    fmt.Printf("product1 last: %+#v\n", product1)
    product1 = Product{}
    err = DB.Take(&product1, "code=?", "D10").Error
    if err != nil {
        fmt.Println(err.Error())
    }
    fmt.Printf("product1 take D10: %+#v\n", product1)
    product1 = Product{}
    err = DB.Take(&product1, fmt.Sprintf("code='%s'", "D9")).Error
    if err != nil {
        fmt.Println(err.Error())
    }
    fmt.Printf("product1 take D9: %+#v\n", product1)

    // 范围查询
    var productArray []Product
    rows := DB.Find(&productArray).RowsAffected
    fmt.Println("rows:", rows)
    data, _ := json.Marshal(productArray)
    fmt.Println("data: ", string(data))
    for _, p := range productArray {
        fmt.Println(p)
    }
    var productArray2 []Product
    rows = DB.Find(&productArray2, "Code in (?)", []string{"D1", "D2"}).RowsAffected
    for _, p := range productArray {
        fmt.Println(p)
    }
    fmt.Println("row:", rows)

    // 单表修改
    DB.Take(&product1, 11)
    product1.Code = "D101"
    product1.Price = 101
    DB.Save(product1)

    // 删除
    var productArray3 []Product
    rows = DB.Delete(&productArray3, []int{1, 2, 3}).RowsAffected
    // rows = DB.Delete(&productArray3).RowsAffected
    fmt.Println("delete rows:", rows)
    /*

       // Update - 将 product 的 price 更新为 200
       db.Model(&product).Update("Price", 200)
       // Update - 更新多个字段
       db.Model(&product).Updates(Product{Price: 200, Code: "F42"}) // 仅更新非零值字段
       db.Model(&product).Updates(map[string]interface{}{"Price": 200, "Code": "F42"})

       // Delete - 删除 product
       db.Delete(&product, 1)
    */
}
