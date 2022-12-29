import QtQuick 2.0

Item{
    width: 1280*3/2
    height: 720*3/2

    Text{
        id: mtxt
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        font.pixelSize: 50*3/2
        text: "app assistant window"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                mtxt.text = widget_context
            }
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.2
    }

    Item{
        width: 1280/4
        height: 720/4
        anchors.centerIn: parent

        Loader{
            id: loaderwidget
            anchors.fill: parent
            sourceComponent: screen_widget
        }
    }
}
