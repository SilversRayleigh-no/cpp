Table Of Contents
1. QQmlEngine
2. QQmlApplicationEngine
3. QQmlContext
4. QQuickView

==================================================================================================================================================================

1. QQmlEngine : public QJSEngine : public QObject
- is a class provides a environment to instance QmlComponents
inherit from : QJSEngine, QJSEngine inherited from QObject
inherited by: QQmlApplicationEngine

=> QQmlApplicationEngine <- QQmlEngine <- QJSEngine <- QObject

#include <QQmlEngine>
Qt += qml

- qmlengine(Qobject*) -> trả về QQmlEngine tương ứng cho cái object đó nếu có: QQmlEngine* engine = qmlEngine(QObject*)
- thằng QQmlEngine thì nó k có cách thuận tiện nào để load 1 file qml, chỉ có thể khởi tạo instance QQmlComponent rồi gọi function create cho nó thôi

*** qmlRegisterType : use to register 1 instantiable object type (dùng để đăng kí 1 C++ Object Type mà có thể khởi tạo được ở trên qml - khởi tạo bao nhiêu instance cũng được) ***

int qmlRegisterType<class>("...", int, int, "...")

- nếu chỉ cần dùng enum thì k cần khởi tạo object trên qml làm gì cả- dùng Q_ENUMS
- class phải phải public QObject, use Q_OBJECT marco, tên dùng trên qml phải bắt đàu bằng chữ hoa
- nếu có dùng Q_PROPERTY thì on change được cả tên property lẫn signal
- call được Q_INVOKABLE và public slots
ví dụ:
class Myclass : public QObject{
	Q_OBJECT
	Q_PROPERTY(QString myname READ getName WRITE setName NOTIFY nameChanged)
public:
	enum Color : int {
		COLOR_GREEN,
		COLOR_RED
	}
signals:
	void nameChanged(QString xxxname);
};

+++ IN CPP: qmlRegisterType<Myclass>("myclass", 1, 0, "Myclass")

+++ IN QML: 
import myclass 1.0

function javafunction(){}

// create 1 instance class Myclass is obj_one, được sở hữu và quản lý bởi java owner ship
MyClass{
	id: obj_one
	// signal changed, trên qml sẽ dùng chính cái tên parameter
	onNameChanged:{
        console.log("signal " + xxxname)
    }
qmlRegisterSingletonType 
    // tên property changed
    onMynameChanged:{
        console.log("onMynameChanged " + xxxname)
    }
}

- có thể connect signal c++ với function trên qml trực tiếp như sau: obj_one.nameChanged.connect(javafunction)

only use: Myclass.COLOR_GREEN, cant obj_one.COLOR_GREEN or cant obj_one.Color.COLOR_GREEN

*** qmlRegisterUncreatableType: use to register non-instantiable object type (dùng để tạo type mà không khởi tạo trên qml) - không cho phép khởi tạo instance 
trên qml ***

*** qmlRegisterSingletonType: chỉ khởi tạo 1 instance duy nhất để dùng trên qml ***

==================================================================================================================================================================

2. QQmlApplicationEngine : public QQmlEngine
- provides a convenient way to load 1 single Qml file, because QQmlEngine do not
- combines QQmlEngine and QQmlComponent to provides a convenient way to load single Qml file 
- QQmlApplicationEngine does not automatically a root window, but QQuickWindow dose

#include <QQmlApplicationEngine>
Qt += qml

- public lại thằng QQmlEngine, có hàm QQmlApplicationEngine::load để load 1 file qml cho nhanh, thực chất bên trong nó cũng instance 1 QQmlComponent* rồi ->create
- tiện thể thì thằng QQuickView khi setSource cũng ý như thế, bên trong hàm setSource cũng tạo 1 instance QQmlComponent rồi gọi hamg create
==================================================================================================================================================================

3. QQmlContext : public QObject
- inherits from QObject
- is a class defines a context within a qml engine: gọi là bối cảnh chắc sẽ hợp lý
- allow data to be exposed to Qml Component instanced by Qml engine: cho phép dữ liệu được available lên trên với qml

#include <QQmlContext>
Qt +=qml

=> như đã nói thì QQmlEngine là mỗi trường để khởi tạo QQmlComponent, (QQmlApplicationEngine thì nó có thể load luôn file qml thì cũng như là 1 qml component thôi) và 
QQmlComponent thì nó phải được khởi tạo bên trong QQmlContext, nghĩa là nó phải được khởi tạo trong 1 bối cảnh cụ thể và xác định. Vì QQmlContext nó là bối cảnh passing 
data từ C++ tới component
- Mỗi 1 engine được tạo ra nó sẽ tạo ra root context tương ứng, sau đó ta có  thể tạo ra nhiều context từ root context này(1 context phải tạo từ 1 context khác)
- và mỗi khi tạo 1 component thì phải xác định nó được tạo với context nào

- ví dụ load file qml bởi hàm load của QQmlApplicationEngine thì là với root context
- tại sao phải xác định, bởi vì nó sẽ xác định xem data từ c++ có thể pass lên qml được hay không
- context property được set từ context cha sẽ được context con kế thừa hết và available với mọi component tạo từ context con
- ngược lại, context property mà chỉ được set tại context con sẽ chỉ available với component tạo từ context con, cant available với component mà tạo từ context cha 

- Chú ý: khi đã có object được create trong context rồi thì việc set context object hoặc là add thêm context property sẽ là hành động expensive, tốt nhất là setup hết 
trước đi rồi hãy create object
ví dụ: có 3 file qml a.qml và b.qml và c.qml

QQmlApplicationEngine engine;
QQmlContext *root = engine.rootContext();
QQmlcontext * child = new QQmlContext(root);

root->setContextProperty("x", 9);
child->setContextProperty("y", 3);
engine.load file a.qml, b.qml

QQmlComponent comp(engine, c.qml);
QObject obj = comp.create(child); // create component comp với context là child

biến x= 9 sẽ available với cả 3 file qml, nhưng biến y= 3 chỉ available với comp

==================================================================================================================================================================

4. QQuickView : public QQuickWindow : public QQWindow : public QObject

- khi mà mình khởi tạo 1 instance QQuickView, thì có 2 TH, 1 là truyền vào 1 tham số là QQmlEngine*, 2 là k có tham số QQmlEngine*, thì nó khác nhau thế nào ?
: khởi tạo 1 instance QQuickView nó luôn gọi hàm init của QQuickViewPrivate trong constructor của QQuickView, trong hàm init đó nó sẽ create 1 QQmlEngine*, nếu mà
mình truyền vào thì nó gán chứ khỏi cần tạo

-> cái việc gọi rootObject hay rootContext là thằng QQmlEngine nó return về
QQuickView::rootContext {
	return QQmlEngine->rootContext()
}

- lý dó mà context nó giống hệt nhau đó, nó là 1
- qmlengine(Qobject*) -> trả về QQmlEngine tương ứng cho cái object đó nếu có: QQmlEngine* engine = qmlEngine(QObject*)

ví dụ:

QQmlEngine* engine_1 = new QQmlEngine;

QQuickView* view = new QQuickView(engine_1);
view.setSource(source_path_qml) 
/* (remember <=> QQmlComponent* component = new QQmlComponent(engine_1, source_path_qml); nếu không truyền vào engine_1 thì nó tự create ra 1 thằng QQmlEngine 
rồi truyền vào component) */

QQmlEngine* engine_2 = qmlEngine(view->rootObject); /* trả về 1 cái engine tương ứng với cái thằng rootObject này */

NOTE: mình sẽ gọi thằng engine ban đầu truyền vào hoặc không truyền engine vào là engine_zero
thì : engine_2 chính là engine_zero, thằng view thì cũng wrap engine_zero

=> ví dụ context: engine_2->rootContext = view->rootContext = engine_zero->rootContext

- mà chung context thì biết rồi đấy, pass data lên qml là nhận như nhau hết

ĐÂY NÈ :
	QQmlEngine* engine_zero = new QQmlEngine;
    QQuickView* view = new QQuickView(engine_zero, nullptr);
    view->setSource(QUrl::fromLocalFile("/home/quyle/untitled/main.qml"));

    QQmlEngine* engine_1 = qmlEngine(view->rootObject());

    qDebug() << "view->rootContext(): " << view->rootContext() << "engine_1->rootContext(): " << engine_1->rootContext() << "engine_zero->rootContext(): " << engine_zero->rootContext(); // is same
    qDebug() << engine_zero << view->engine(); // is same








