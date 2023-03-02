class base {
public:
    virtual void funcBase() {}
};

class derived : public base {
public:
    virtual void funcBase() {}
    virtual void funcDerived() {} // I add virtual keyword to make sure funcDerived method is added in vtable of class
};

int main()
{
    base* obj = new derived;
    obj->funcBase(); // will print funcBase in class derived -> it's normal

    obj->funcDerived(); // error: 'class base' has no member named 'funcDerived'
    return 0;
}

nhìn lại vào dòng code : base* obj = new derived;
-> tại thời điểm biên dịch, thì complier sẽ kiểm tra xem class derived có kế  thừa class base hay không, 
Nếu có, thì con trỏ "obj" được tạo ra là kiểu "base*" và được gán trỏ tới một đối tượng của lớp "derived" là hợp lệ, tại đây sẽ không có khởi tạo vùng nhớ
cho object bởi new, do đó trình biên dịch chưa thể biết chính xác kiểu của đối tượng, chỉ đến khi chương trình chạy, vùng nhớ được khởi tạo, con trỏ trỏ tới,
lúc đó mới biết là chính xác đối tượng đó là kiểu derived
-> vậy nên lỗi là tại thời điểm complie,complier không biết được rằng obj có trỏ đến 1 object kiểu derived thật không hay chỉ là 1 kiểu khác kế thừa base,
nếu không thì gọi funcDerived là hoàn toàn sai rồi