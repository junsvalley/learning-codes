package main

import (
	"fmt"
	"reflect"
)

type DataValue struct {
	Vtype string
	Val   interface{}
}

func (d *DataValue) SetInt32(v int32) {
	d.Vtype = "C_INT32"
	d.Val = v
}

func (d *DataValue) SetString(v string) {
	d.Vtype = "C_STRING"
	d.Val = v
}

func (d DataValue) GetString() string {
	return d.Val.(string)
}

func main() {
	var a DataValue
	a.SetInt32(22)
	v := reflect.ValueOf(a)
	t := reflect.TypeOf(a)
	i := reflect.New(t).CanSet()
	fmt.Println(v, v.Kind(), t, i, reflect.Ptr)

	fmt.Println(t.NumField())
	for i := 0; i < t.NumField(); i++ {
		fmt.Println(t.Field(i))
	}

	fmt.Println(t.NumMethod())
	for i := 0; i < t.NumMethod(); i++ {
		fmt.Println(t.Method(i))
	}

	f := v.MethodByName("GetString")
	fmt.Println("func is:", f)
	//	in := make([]reflect.Value, 0)
	//	out := f.Call(in)
	//	fmt.Println(out)

	var d *DataValue = &DataValue{"C_UNKNOW", "UNSET"}
	v2 := reflect.ValueOf(d)
	t2 := reflect.ValueOf(d)
	fmt.Println(v2.Kind(), t2.Kind(), v2.Elem(), v2.Type())
}

//package main

//import (
//	"fmt"
//	"reflect"
//)

//type User struct {
//	Name string
//	Age  int
//	Id   string
//}

//func (u User) SayHello(name string) {
//	fmt.Println("hello, ", name, "! my name is ", u.Name)
//}

//func main() {
//	u := User{Name: "mckee", Age: 20, Id: "user100"}

//	//hello,  Jack ! my name is  mckee
//	reflect.ValueOf(u).MethodByName("SayHello").Call([]reflect.Value{reflect.ValueOf("Jack")})
//}
