// go get github.com/tidwall/gjson
// https://darjun.github.io/2020/03/22/godailylib/gjson/

package main

import (
	"fmt"
  
	"github.com/tidwall/gjson"
  )
  
  func main() {
	json := `{"name":{"first":"li","last":"dj"},"age":18}`
	lastName := gjson.Get(json, "name.last")
	fmt.Println("last name:", lastName.String())
  
	age := gjson.Get(json, "age")
	fmt.Println("age:", age.Int())
  }

/*
使用很简单，只需要传入 JSON 串和要读取的键路径即可。
注意一点细节，因为gjson.Get()函数实际上返回的是gjson.Result类型，
我们要调用其相应的方法进行转换对应的类型。如上面的String()和Int()方法。
如果是直接打印输出，其实可以省略String()，
fmt包的大部分函数都可以对实现fmt.Stringer接口的类型调用String()方法。
键路径实际上是以.分隔的一系列键。gjson支持在键中包含通配符*和?，*匹配任意多个字符，
?匹配单个字符，例如ca*可以匹配cat/cate/cake等以ca开头的键，ca?只能匹配cat/cap等
以ca开头且后面只有一个字符的键。
数组使用键名 + . + 索引（索引从 0 开始）的方式读取元素，如果键pets对应的值是一个数组，
那么pets.0读取数组的第一个元素，pets.1读取第二个元素。
数组长度使用**键名 + . + #**获取，例如pets.#返回数组pets的长度。
如果键名中出现.，那么需要使用\进行转义。
*/

package main

const json = `
{
  "name":{"first":"Tom", "last": "Anderson"},
  "age": 37,
  "children": ["Sara", "Alex", "Jack"],
  "fav.movie": "Dear Hunter",
  "friends": [
    {"first": "Dale", "last":"Murphy", "age": 44, "nets": ["ig", "fb", "tw"]},
    {"first": "Roger", "last": "Craig", "age": 68, "nets": ["fb", "tw"]},
    {"first": "Jane", "last": "Murphy", "age": 47, "nets": ["ig", "tw"]}
  ]
}
`

func main() {
  fmt.Println("last name:", gjson.Get(json, "name.last"))
  fmt.Println("age:", gjson.Get(json, "age"))
  fmt.Println("children:", gjson.Get(json, "children"))
  fmt.Println("children count:", gjson.Get(json, "children.#"))
  fmt.Println("second child:", gjson.Get(json, "children.1"))
  fmt.Println("third child*:", gjson.Get(json, "child*.2"))
  fmt.Println("first c?ild:", gjson.Get(json, "c?ildren.0"))
  fmt.Println("fav.moive", gjson.Get(json, `fav.\moive`))
  fmt.Println("first name of friends:", gjson.Get(json, "friends.#.first"))
  fmt.Println("last name of second friend:", gjson.Get(json, "friends.1.last"))
}

