Dbus linux có 2 loại là system bus và session bus, và cứ hiểu là được quản lý bởi 1 cái central bus(bus trung tâm) đi
- system bus: có 1 system bus, nó được run như là system-level service (dịch vụ cấp hệ thống), các dịch vụ toàn hệ thống có thể truy cập được trên đó
- session bus: có thể k có hoặc có nhiều session bus, mỗi session bus sẽ chỉ dành cho 1 phiên người dùng (user session)

thì dù là system hay session bus thì có mỗi người dùng đều chạy các process kiểu như vào google, work, bật Qt ... để làm cv mong muốn, thì có phải mỗi cái là 1 process 
riêng chưa
- vậy thì nếu tại đâu đó trong process này mình đăng kí 1 service bus, thì cái central bus nó sẽ biết được là cái process này đang đkí cái serivce này => nó sẽ điều hướng
đúng

-> 1 máy tính nhúng như kiểu con board trong ô tô gồm nhiều ứng dụng cấu thành như apphome, appmedia, notifycationmanage, apposdmanager... thì có phải mỗi 1 thằng app 
nó run nó đều là 1 process riêng ko, thì mình đều cần tại trong mỗi process đkí cho nó 1 cái serive name, thì có phải bây giờ cái process-hay là cái app đó nó được thằng 
central bus biết đến như là serivce name => registerService(const QString &serviceName);

Theo Qt document, communicating sảy ra thông qua 1 central server application, gọi là bus
khi communicating trên bus, ứng dụng nó sẽ được hiểu hay là được gọi là service name, đây là cách mà ứng dụng chọn để được biết đến bởi ứng dụng khác, sẽ giải thích chỗ này kĩ hơn
- interface nó giống như 1 lớp C++ trừu tượng, nó như 1 bản hợp đồng về signal và method giữa thằng call và thằng nhận => bắt buộc phải có interface cả khi emit signal hay 
call slot

- nếu connect createMethodCall tới 1 service k được register nó sẽ báo là service không được provided bởi bất kì file .service nào, vậy khả năng là khi registerService thì 
nó sẽ tạo ra 1 file .serive với các trường info ở đâu đó trong hệ thống

=> trên Bus Server là chỗ communicating, prorcess nó sẽ registerService lên bus server đó, khi đó nó cái process đó sẽ được biết đến như là servicename, đây là cách để Bus
Server quản lý , chứ k phải thông qua cái tên ứng dụng hay là gì khác

- object trong process thì sẽ có đăng kí path, khi này đã cụ thể object có path và có service, và có interface

*** Khi mình nói process, cũng hiểu đơn giản là trong 1 app, trong 1 project ***

*** Về service, cách để đăng kí 1 service là: bool registerService(const QString &serviceName);

	QDBusConnection bus = QDBusConnection::sessionBus(); // systemBus or sessionBus
    bool ret = bus.registerService("vlxx.com.vn");

- đăng kí service lên máy chú DBus, đăng kí thành công thì serivce sẽ represent cho cái process mà nó được đăng kí, không thể đăng kí lại ở process này hay bất kì process nào khác nữa
- có thể registerService tại bất kì đâu trong process, vì nó represent cho process chứ k phải cho bất kì 1 class nào
- 1 process có thể đăng kí nhiều service name, và dĩ nhiên tất cả chúng đều ngang hàng và available với tất cả object trong process này
=> mỗi process cũng chỉ cần 1 service thôi

*** Về path và interface ***
- path và interface thì liên quan trực tiếp tới từng class
- cách đkí: 
			bool registerObject(const QString &path, QObject *object,
                        RegisterOptions options = ExportAdaptors);

	Hoặc	

    	(2)	bool registerObject(const QString &path, const QString &interface, QObject *object,
                        RegisterOptions options = ExportAdaptors);

- sẽ luôn cần dùng registerObject để đăng kí path cho object
- còn interface ta có thể đăng kí ở dây, cách thứ 2 là dùng file xml, gen ra file adaptor và file interface, đăng kí class tới adaptor => interface trong adaptor available với mọi class
đăng kí tới 

- có thể đăng kí nhiều path, nhiều interface cho cùng 1 class cho cùng 1 class
- đăng kí theo cách (2) thì interface nào phải đi với path đó, còn đăng kí interface theo class adaptor được gen ra thì linh hoạt hơn
- trong file xml có nhiều interface, mỗi interface sẽ gen ra 1 class adaptor riêng, cần dùng interface nào thì đăng kí với class adaptor đó

ví dụ:
class A: registerObject(const QString &path_1, const QString &interface_1, this, RegisterOptions options = ExportAdaptors);
		 registerObject(const QString &path_2, const QString &interface_2, this, RegisterOptions options = ExportAdaptors);

		QDBusMessage::createMethodCall(QString(service),path_1,interface_1,SLOT(slot));
		but can not do: QDBusMessage::createMethodCall(QString(service),path_1,interface_2,SLOT(slot));
						QDBusMessage::createMethodCall(QString(service),path_2,interface_1,SLOT(slot));

Cách xml:

class A: registerObject(const QString &path_1, this, RegisterOptions options = ExportAdaptors);
		 registerObject(const QString &path_2, this, RegisterOptions options = ExportAdaptors);

<node>
    <interface name="interface_1">
        <method name="SetBeepOne">
            <arg type="i" direction="in"/>
        </method>
    </interface>
    <interface name="interface_2">
    <method name="SetBeepTwo">
        <arg type="i" direction="in"/>
    </method>
    </interface>
</node>

-> gen ra 2 class AdaptorOne chứa interface_1, class AdaptorTwo chứa interface_2
muốn dùng interface_x thì new Adaptor***(this)

lúc này: new AdaptorOne(this), new AdaptorTwo(this)
  
	QDBusMessage::createMethodCall(QString(service),path_1,interface_2,SLOT(slot));
	QDBusMessage::createMethodCall(QString(service),path_2,interface_1,SLOT(slot));

=> 	ALL WILL BE OK

- nếu kế thừa, khi class cha đã đkí đến adaptor rồi, thì class con k cần nữa, nghĩa là path và interface sẽ được apply luôn cho các class con, cả khi adaptor để ở mode private
khi connect signal slot, thì cơ chế run hàm cũng được áp dụng theo tính chất đa hình
- signals chính là public
- nếu class con muốn độc lập bắn signal trong adaptor mà lại k khai báo ở class cha thì class cũng phải tự đi đkí đến adaptor !

*** Khi call method, function có thể có giá trị return về ***

- có thể nhận được giá trị trả về
ví dụ:
QString QDbusTwo::slotFromTwo(){
    qDebug() << "slot from two : ";
    return QString("Le Ngoc Hai");
}

	QDBusMessage response = QDBusConnection::sessionBus().call(msg_g, QDBus::Block, 100);
    if (response.type() != QDBusMessage::ReplyMessage) {
        qDebug() << "error log: " << response.errorMessage();
    }
    if(response.arguments().count()){
        QString text = response.arguments().at(0).toString();
        qDebug() << "text == " << text;
    }else{
        qDebug() << response.errorMessage();
    }

- sử dụng arguments()


- createSignal, createMethod call là dynamic - k cần dùng đến file xml cũng được và k cần đến instance của adaptor và proxy
- dùng theo file xml là static, thích thì có thể dùng đến instance của adaptor và proxy
- Adaptor là bộ điều hướng cho object, object emit signal thì adaptor emit signal đó, adaptor call method thì object cũng call method đó
- Proxy là đối tượng điều khiển object từ xa