func DeepCopyByMap(src interface{}, des interface{}, white map[string]bool) (err error) {
    if src == nil || des == nil {
        return fmt.Errorf("DeepCopy Error, src or des is nil")
    }

    if reflect.TypeOf(src).Kind() != reflect.TypeOf(des).Kind() {
        return fmt.Errorf("DeepCopy Error, src ans des is not the same type")
    }

    srcType := reflect.TypeOf(src)
    srcValue := reflect.ValueOf(src)
    // desType := reflect.TypeOf(des)
    desValue := reflect.ValueOf(des)
    for i := 0; i < srcType.Elem().NumField(); i++ {
        filed := srcValue.Elem().Type().Field(i).Name
        if white != nil && len(white) > 0 {
            if _, ok := white[filed]; ok {
                continue
            }
        }
        desFiled := desValue.Elem().FieldByName(filed)
        if desFiled.CanSet() {
            desFiled.Set(srcValue.Elem().FieldByName(filed))
        }
    }
    return nil
}
