string toLowerCase(string str) {
    if (str.empty()) return "";
    for (int i = 0; i < str.size(); i++) {
        if(isupper(str[i]))
            str[i] += 32;
        else
            continue;
    }
    return str;
}