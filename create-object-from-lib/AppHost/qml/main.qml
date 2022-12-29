import QtQuick 2.0

Item{
    width: 1280
    height: 720

    Rectangle{
        anchors.fill: parent
        color: "green"
        opacity: 0.2
    }

    Text{
        id: mtxt
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        font.pixelSize: 50
        text: "app host engine"
        MouseArea{
            anchors.fill: parent
            onClicked: {
                mtxt.text = widget_context
            }
        }
    }

    Item{
        width: 1280*3/2
        height: 720*3/2
//        anchors.centerIn: parent

        Loader{
            id: loaderwidget
            anchors.fill: parent
            sourceComponent: AW_Screen
        }
    }

}
