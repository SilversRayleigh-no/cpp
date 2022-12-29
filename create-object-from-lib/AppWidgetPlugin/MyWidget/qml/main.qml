import QtQuick 2.0

Item{
//    width: 1280/4
//    height: 1024/4

    Rectangle{
        anchors.fill: parent
        color: "purple"
        opacity: 0.2

        Text{
            id:mtxt
            anchors.centerIn: parent
            font.pixelSize: 50/4
            text: "app widget - my widget"
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                mtxt.text = widget_context
            }
        }
    }
}
